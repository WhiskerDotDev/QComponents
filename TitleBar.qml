import QtQuick;

// Rectangle{
//       id: root;
//       anchors{
//       left: parent.left; right: parent.right;
//       top: parent.top;
//       }
//       required property Window win;
//       property bool fullScreenOnMaximize: true;
//       property bool enableResize: true;
//       property bool enableDragging : true;
//       smooth: false; antialiasing: false;
//       property MouseArea hitbox : MouseArea{
//             parent: root;
//             anchors.fill: parent;
//             preventStealing: false;
//             hoverEnabled: false; scrollGestureEnabled: false;
//             onPressed:()=>{ if(root.enableDragging === false){return;} root.win.startSystemMove(); }
//             onDoubleClicked : ()=>{
//                                     if(root.enableResize === false){return;}
//                                     if(root.fullScreenOnMaximize === true){
//                                           if(root.win.visibility !== Window.FullScreen){
//                                                 root.win.visibility = Window.FullScreen;}else{root.win.visibility = Window.Windowed;}
//                                     }else{
//                                           if(root.win.visibility !== Window.Maximized){
//                                                 root.win.visibility = Window.Maximized;}else{root.win.visibility = Window.Windowed;}
//                                     }
//                               }
//       }
// }

MouseArea{
      id: rootpane;
      visible: true;
      anchors{
            left: parent.left;
            right: parent.right;
            top: parent.top;
      }
      required property Window win;
      property Item content: null;
      property bool fullScreenOnMaximize: true;
      property bool enableResize: true;
      property bool enableDragging : true;
      preventStealing: false;
      hoverEnabled: false; scrollGestureEnabled: false;
      onPressed:()=>{ if(rootpane.enableDragging === false || win.visibility === Window.FullScreen){return;} rootpane.win.startSystemMove(); }
      onDoubleClicked: ()=>{
                             if(rootpane.enableResize === false){return;}

                             if(rootpane.fullScreenOnMaximize === true){
                                   if(rootpane.win.visibility !== Window.FullScreen){
                                         rootpane.win.visibility = Window.FullScreen;}else{rootpane.win.visibility = Window.Windowed;}
                             }else{
                                   if(rootpane.win.visibility !== Window.Maximized){
                                         rootpane.win.visibility = Window.Maximized;}else{rootpane.win.visibility = Window.Windowed;}
                             }

                       }
      Component.onCompleted:()=>{
                                  if(content !== null){
                                        content.parent = rootpane;
                                        content.anchors.fill = rootpane;
                                        content.z = rootpane.z;
                                  }
                            }

}