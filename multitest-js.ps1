param(
[int]$maxtests=100
)
Write-Host "-------nodejs time test-------"
Write-Host "skiped first value:" ((Measure-Command {node ./opt_test.js}).Milliseconds)
$mttime = 0
$counts = 0
for ($d=0; $d -le $maxtests-1; $d = $d + 1) {
	$temp = (Measure-Command {node ./opt_test.js}).Milliseconds
	$counts = $counts + 1 
	$mttime = $mttime + $temp
}
$mttime = $mttime / $counts
Write-Host (("Milliseconds: {0:f2}" -f $mttime) + " by " + $counts + " tests")
Add-Content	-Path "test.log" -Value ("js: " + $mttime + " by " + $counts + " tests")

