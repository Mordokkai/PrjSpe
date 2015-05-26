proc exportToSDK {} {
  cd /tima/smancini/zybo_cam/zybo_simple
  if { [ catch { xload xmp system.xmp } result ] } {
    exit 10
  }
  if { [run exporttosdk] != 0 } {
    return -1
  }
  return 0
}

if { [catch {exportToSDK} result] } {
  exit -1
}

set sExportDir [ xget sdk_export_dir ]
set sExportDir [ file join "/tima/smancini/zybo_cam/zybo_simple" "$sExportDir" "hw" ] 
if { [ file exists /tima/smancini/zybo_cam/zybo_cam_ise/zybo_cam/edkBmmFile_bd.bmm ] } {
   puts "Copying placed bmm file /tima/smancini/zybo_cam/zybo_cam_ise/zybo_cam/edkBmmFile_bd.bmm to $sExportDir" 
   file copy -force "/tima/smancini/zybo_cam/zybo_cam_ise/zybo_cam/edkBmmFile_bd.bmm" $sExportDir
}
if { [ file exists /tima/smancini/zybo_cam/zybo_cam_ise/zybo_cam/system_top.bit ] } {
   puts "Copying bit file /tima/smancini/zybo_cam/zybo_cam_ise/zybo_cam/system_top.bit to $sExportDir" 
   file copy -force "/tima/smancini/zybo_cam/zybo_cam_ise/zybo_cam/system_top.bit" $sExportDir
}
exit $result
