"C:\Program Files\MRE SDK V3.0.00\tools\DllPackage.exe" "D:\MyGitHub\Textvp\Textvp.vcproj"
if %errorlevel% == 0 (
 echo postbuild OK.
  copy Textvp.vpp ..\..\..\MoDIS_VC9\WIN32FS\DRIVE_E\Textvp.vpp /y
exit 0
)else (
echo postbuild error
  echo error code: %errorlevel%
  exit 1
)

