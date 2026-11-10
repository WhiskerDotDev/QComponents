import QtQuick;

Row{
      id: root;
      property point btnsize;
      property point btn_i_size;
      required property Window win;
      property bool fullScreenOnMaximize: true;
      layoutDirection: Qt.RightToLeft;
      spacing: 0;
      anchors.top: parent.top;
      anchors.right: parent.right; // aligning to topright
      visible : true;
      IconButton{
            color: "red";
            visible: parent.visible;
            id:closeBtn;
            size: root.btnsize; i_size: root.btn_i_size;
            hitbox.onSingleTapped: ()=>{ Qt.quit(); }
      }
      IconButton{
            color: root.win.color
            visible: parent.visible;
            id: maxminBtn;
            size: root.btnsize; i_size: root.btn_i_size;
            hitbox.onSingleTapped: ()=>{
                                    if(root.fullScreenOnMaximize === true){
                                          if(root.win.visibility !== Window.FullScreen){
                                                root.win.visibility = Window.FullScreen;}else{root.win.visibility = Window.Windowed;}
                                    }else{
                                          if(root.win.visibility !== Window.Maximized){
                                                root.win.visibility = Window.Maximized;}else{root.win.visibility = Window.Windowed;}
                                    }
                              }
      }

      IconButton{
            color: root.win.color
            visible: parent.visible;
            id: minimizeBtn;
            size: root.btnsize; i_size: root.btn_i_size;
            hitbox.onSingleTapped: ()=>{root.win.showMinimized();}
      }

      property alias closeButton : closeBtn;
      property alias minmaxButton : maxminBtn;
      property alias minimizeButton : minimizeBtn;

      property alias closeButtonIcon: closeBtn.iconsrc;
      property alias minmaxButtonIcon: maxminBtn.iconsrc;
      property alias minimizeButtonIcon : minimizeBtn.iconsrc;

}
