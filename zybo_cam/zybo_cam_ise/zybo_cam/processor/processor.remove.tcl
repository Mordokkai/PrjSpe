cd /tima/smancini/zybo_cam/zybo_cam_ise/zybo_cam/processor
if { [ catch { xload xmp processor.xmp } result ] } {
  exit 10
}
xset intstyle default
save proj
exit 0
