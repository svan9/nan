param(
[int]$maxtests=100
)
Write-Host "-------cpp time test-------"
Write-Host "skiped first value:" ((Measure-Command {./build/opt-test/opt_test.exe}).Milliseconds)
$mttime = 0
$counts = 0
for ($d=0; $d -le $maxtests-1; $d = $d + 1) {
	$temp = (Measure-Command {./build/opt-test/opt_test.exe}).Milliseconds
	$counts = $counts + 1 
	$mttime = $mttime + $temp
}
$mttime = $mttime / $counts
Write-Host (("Milliseconds: {0:f2}" -f $mttime) + " by " + $counts + " tests")
Add-Content	-Path "test.log" -Value ("cpp: " + $mttime + " by " + $counts + " tests")
