proc pnsynth {} {
  cd /tima/smancini/zybo_cam/processor
  if { [ catch { xload xmp processor.xmp } result ] } {
    exit 10
  }
  if { [catch {run netlist} result] } {
    return -1
  }
  return $result
}
if { [catch {pnsynth} result] } {
  exit -1
}
exit $result
