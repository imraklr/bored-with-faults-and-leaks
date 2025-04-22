param(
    [Parameter(Mandatory=$false)]
    [ValidateSet('Debug', 'Release')]
    [string]$BuildType = 'Debug',

    [Parameter(Mandatory=$false)]
    [ValidateSet($true, $false)]
    [switch]$Clean = $false
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

function BuilderFunction {
    param (
        [Parameter(Mandatory=$false)]
        [string]$LocationStackName          # Optional
    )
    # Make platform-specific builds
    if($IsWindows) {
        # Windows specific build method (uses Visual Studio 17 2022 as the generator)
        Invoke-Command -ScriptBlock {
            cmake -G "Visual Studio 17 2022" .. -DCODE_CONFIGURATION_TYPE:string=$BuildType
        } -NoNewScope -ErrorAction Stop
        Invoke-Command -ScriptBlock {
            cmake --build . --config $BuildType
        } -NoNewScope -ErrorAction Stop
    } elseif($IsLinux) {
        # Linux specific build implementations
    }
}

function RunTests {
    param(
        [Parameter(Mandatory=$false)]
        [string]$LocationStackName
    )
    # navigate to the build directory
    if ($LocationStackName) {
        Set-Location $(Get-Location)
    } # Navigation to the build directory is done from the caller of RunTests function
    # Run tests with build configuration specified in Invoke-Command
    Invoke-Command -NoNewScope -ScriptBlock {
        # test with the build type
        ctest -C $BuildType
    }
}


$StartLocation = $(Get-Location)

# look for build directory
if ((Test-Path -Path "$(Get-Location)/build") -eq $false) {
    # make the build directory (no cleaning required)
    New-Item -Path $(Get-Location) -ItemType Directory -Name 'build'
    # move to the build directory
    Set-Location -Path 'build'

    # Continue with build (use BuilderFunction)
    BuilderFunction

    # Continue with tests
    RunTests

} else {
    # move to the build directory
    Set-Location -Path 'build'
    # clean the build directory if flag specified so
    if ($Clean) {
        # clean the build directory
        Get-ChildItem -Path $(Get-Location) | Remove-Item -Recurse -Force
    } # else simply continue with the build
    # Continue with build (use BuilderFunction)
    BuilderFunction

    # Continue with tests
    RunTests
}

# If any error encountered, restore start path
Set-Location $StartLocation