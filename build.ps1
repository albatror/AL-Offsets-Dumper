if (Test-Path -Path '.\release') { Remove-Item -Force -Recurse -Path '.\release' }
New-Item -ItemType Container -Path '.\release'

msbuild `
    -p:Configuration='Release' `
    -p:Platform='x64' `
    '.\Apex Legends\Apex Legends.vcxproj'
if (-Not $?) { exit $lastExitCode }
Copy-Item -Force -Path '.\Apex Legends\bin\Release\Apex Legends.exe' '.\release'

exit 0
