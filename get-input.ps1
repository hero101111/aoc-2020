  param($day)
  
  $downloadToPath = "C:\Work\aoc-2020\AocSolutions\inputs\Day$day\input.txt"
  $remoteFileLocation = "https://adventofcode.com/2020/day/$day/input"
  
  $session = New-Object Microsoft.PowerShell.Commands.WebRequestSession
    
  $cookie = New-Object System.Net.Cookie 
    
  $cookie.Name = "session"
  $cookie.Value = $env:AOC_SESSION
  $cookie.Domain = ".adventofcode.com"

  $session.Cookies.Add($cookie);

  Invoke-WebRequest $remoteFileLocation -WebSession $session -TimeoutSec 900 -OutFile $downloadToPath