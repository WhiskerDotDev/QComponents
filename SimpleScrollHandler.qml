import QtQuick;

WheelHandler{
id: root;

signal wheelUp;
signal wheelDown;
onWheel: (wheel)=>{
  if (wheel.angleDelta.y > 0){ root.wheelUp(); } // Wheel up
  else if(wheel.angleDelta.y < 0) { root.wheelDown(); } // Wheel down
}
}