param(
[int]$maxtests=100
)
Write-Host "-------python time test-------"
Write-Host "skiped first value:" ((Measure-Command {python ./opt_test.py}).Milliseconds)
$mttime = 0
$counts = 0
for ($d=0; $d -le $maxtests-1; $d = $d + 1) {
	$temp = (Measure-Command {python ./opt_test.py}).Milliseconds
	$counts = $counts + 1 
	$mttime = $mttime + $temp
}
$mttime = $mttime / $counts
Write-Host (("Milliseconds: {0:f2}" -f $mttime) + " by " + $counts + " tests")
Add-Content	-Path "test.log" -Value ("py: " + $mttime + " by " + $counts + " tests")

