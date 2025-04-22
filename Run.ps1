param(
    [Parameter(Mandatory=$true)]
    [ValidateSet('Debug', 'Release')]
    [string]$RunType = 'Debug'
)

# Check if CMake is installed
try {
    # Attempt to get the CMake version
    $cmakeVersion = cmake --version
    Write-Host "CMake is installed: $cmakeVersion"
} catch {
    # If an error occurs, CMake is not installed
    Write-Host "CMake is not installed. Terminating the script."
    exit 1
}

function PlatformSpecificCall {
    # Run the application
    if($IsWindows -eq $true) {
        # Windows specific instructions to run the built application
        Invoke-Command -ScriptBlock {
            ./*.exe
        } -NoNewScope -ErrorAction Stop
    } elseif($IsLinux -eq $true) {
        # Linux specific instructions to run the built application
    } elseif($IsMacOS -eq $true) {
        # MacOS specific instructions to run the built application
    }
}


# Run the application
$StartLocation = $(Get-Location)

# Look for build directory
if((Test-Path -Path "$(Get-Location)/build") -eq $false) {
    # exit, as the project has not yet been built
    Write-Error -Message 'No build directory found, build required!!!'
} else {
    # move to the build directory
    Set-Location -Path 'build'
    # Check if the build type directory exists
    if((Test-Path -Path "$(Get-Location)/$($RunType)") -eq $true) {
        # Visit build type directory
        Set-Location -Path $RunType
        PlatformSpecificCall
    } else {
        Write-Error -Message 'No build directory foound for the respective build type, build required!!!'
    }
}

Set-Location $StartLocation