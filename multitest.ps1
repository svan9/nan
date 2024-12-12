param(
[int]$maxtests=100
)
Write-Host "-------nanvma time test-------"
Write-Host "skiped first value:" ((Measure-Command {.\build\bin\nanvma.exe .\build\bin\hellow_word.nb}).Milliseconds)
$mttime = 0
$counts = 0
for ($d=0; $d -le $maxtests-1; $d = $d + 1) {
	$temp = (Measure-Command {.\build\bin\nanvma.exe .\build\bin\hellow_word.nb}).Milliseconds
	$counts = $counts + 1 
	$mttime = $mttime + $temp
}
$mttime = $mttime / $counts
Write-Host (("Milliseconds: {0:f2}" -f $mttime) + " by " + $counts + " tests")
