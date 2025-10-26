# Prompt user for the executable path

# Start process and capture details with exec args
$process = Start-Process -FilePath "e:\so2u\GITHUB\cuba\nan\build\bin\nanvm.exe" -ArgumentList "e:\so2u\GITHUB\cuba\nan\nan-temp.nb" -PassThru

$maxMemory = 0

# Monitor process memory until it exits
while (-not $process.HasExited) {
    try {
        $currentMemory = (Get-Process -Id $process.Id).WorkingSet64
        if ($currentMemory -gt $maxMemory) {
            $maxMemory = $currentMemory
        }
    } catch {
        # Process may have exited
    }
    Start-Sleep -Milliseconds 500
}

# Final check in case the process exited before the last loop iteration
try {
    $finalMemory = (Get-Process -Id $process.Id -ErrorAction SilentlyContinue).WorkingSet64
    if ($finalMemory -gt $maxMemory) {
        $maxMemory = $finalMemory
    }
} catch {
    # Process is not available
}

Write-Output "Maximum memory usage: $maxMemory bytes"
