import QtQuick;

BasicButton{
id:root;

BorderImage {
      id: decor;
      z: parent.z;
      width: parent.width;
      height: parent.height;
      horizontalTileMode: BorderImage.Repeat; verticalTileMode: BorderImage.Repeat;
      smooth: false; antialiasing: false;
}

}