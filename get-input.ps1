param($day)
  
if ($day -eq $null) {
  $day = (Get-Date).Day
}
  
$downloadToPath = "C:\Work\aoc-2020\AocSolutions\inputs\Day$day\input.txt"
if (!(Test-Path C:\Work\aoc-2020\AocSolutions\inputs\Day$day)) {
  New-Item -Path "C:\Work\aoc-2020\AocSolutions\inputs\" -name "Day$day" -ItemType "directory" 
}
$remoteFileLocation = "https://adventofcode.com/2020/day/$day/input"
  
$session = New-Object Microsoft.PowerShell.Commands.WebRequestSession
    
$cookie = New-Object System.Net.Cookie 
    
$cookie.Name = "session"
$cookie.Value = $env:AOC_SESSION
$cookie.Domain = ".adventofcode.com"

$session.Cookies.Add($cookie);

Invoke-WebRequest $remoteFileLocation -WebSession $session -TimeoutSec 900 -OutFile $downloadToPath