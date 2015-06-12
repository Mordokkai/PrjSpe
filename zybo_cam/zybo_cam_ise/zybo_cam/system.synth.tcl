proc pnsynth {} {
  cd /user/1/.base/chatouik/home/Projet_specialite/PrjSpe/zybo_cam/zybo_simple
  if { [ catch { xload xmp system.xmp } result ] } {
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
