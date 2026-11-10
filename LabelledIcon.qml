import QtQuick;

Grid{
      id: rootGrid;
      property int iconWidth: Math.round(rootGrid.width / 2);
      // setting either columns or rows to 1 can allow them to be stacked or side-by-side in any variation.
      smooth: rootGrid.smooth; antialiasing: rootGrid.antialiasing;
      horizontalItemAlignment: Grid.AlignHCenter; verticalItemAlignment: Grid.AlignVCenter;
      property url source: "";
      columns: 2; rows: 1;
      spacing: 3;


      property Image icon: Image{
            parent: rootGrid;
            height: rootGrid.height;
            width: rootGrid.iconWidth;
            smooth: rootGrid.smooth; antialiasing: rootGrid.antialiasing;
            source: rootGrid.source;
            // mipmap: false;
            asynchronous: true;
            cache: true;
            fillMode: Image.PreserveAspectFit;
      }

      property Text label : Text{
            parent: rootGrid;
            height: rootGrid.height;
            width: rootGrid.width - rootGrid.iconWidth;
            smooth: rootGrid.smooth; antialiasing: rootGrid.antialiasing;
            wrapMode: Text.Wrap;
            minimumPixelSize: 1;
            fontSizeMode: Text.Fit;
            textFormat: Text.PlainText;
            horizontalAlignment: Text.AlignHCenter;
            verticalAlignment: Text.AlignVCenter;
            color: "#000000";
      }


}