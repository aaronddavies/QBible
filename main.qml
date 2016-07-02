import QtQuick 2.6
import QtQuick.Controls 1.2

ApplicationWindow {
    property int title_column_width: 130
    property int chapter_column_width: 40
    property int column_spacing : 5
    property int row_height: 30
    property int font_size: 12
    property int rect_radius: 2
    property string border_color: font_color
    property int border_width: 1

    property string font_color: "#CCC"
    property string background_color: "#111"
    property string highlight_color: "#0081E9"

    property int current_book: 1
    property int current_chapter: 1
    property int app_border_width: 1

    property int default_width: 800
    property int default_height: 600

    visible: true
    color: background_color
    height: default_height
    width: default_width

    Rectangle {
        color: "transparent"
        border.width: app_border_width
        border.color: font_color
        anchors.fill: parent
    }

    Column {
        width: parent.width
        height: parent.height

        Row {
            id: search_row
            spacing: column_spacing
            width: parent.width - column_spacing
            height: row_height
            z: 1

            Rectangle {
                color: "black"
                width: parent.width - title_column_width
                height: parent.height
                border.color: font_color
                border.width: border_width
                radius: rect_radius
                TextEdit {
                    id: search_box
                    color: font_color
                    text: ""
                    font.pointSize: font_size
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    anchors.leftMargin: column_spacing
                    onFocusChanged: {
                        text = ""
                    }
                }
            }

            IndexButton {
                width: title_column_width
                height: parent.height
                text: "Search"
                fetchOnClick: function () {
                    search_model.search(search_box.text);
                    search_window.visible = true;
                    reading_window.visible = false;
                    search_window.positionViewAtBeginning();
                }
            }
        }

        Row {
            spacing: column_spacing
            width: parent.width
            height: parent.height - row_height

            // Books
            Rectangle {
                width: title_column_width
                color: "transparent"
                height: parent.height
                ListView {
                    id: book_list
                    model: 66
                    anchors.fill: parent
                    delegate: IndexButton {
                        width: parent.width
                        text: scripture_model.bookTitle(index + 1)
                        highlight: index + 1 === current_book
                        fetchOnClick: function () {
                            search_box.focus = false;
                            search_window.visible = false;
                            reading_window.visible = true;
                            current_book = index + 1;
                            current_chapter = 1;
                            scripture_model.fetch(current_book, 1);
                            chapter_list.model = scripture_model.chapterCount();
                            reading_window.positionViewAtBeginning();
                        }
                    }
                }
            }

            // Chapters
            Rectangle {
                width: chapter_column_width
                color: "transparent"
                height: parent.height
                ListView {
                    id: chapter_list
                    model: scripture_model.chapterCount()
                    anchors.fill: parent
                    delegate: IndexButton {
                        width: parent.width
                        text: index + 1
                        highlight: index + 1 === current_chapter
                        fetchOnClick: function () {
                            search_box.focus = false;
                            search_window.visible = false;
                            reading_window.visible = true;
                            current_chapter = index + 1;
                            scripture_model.fetch(current_book, current_chapter);
                            reading_window.positionViewAtBeginning();
                        }
                    }
                }
            }

            // Words
            Rectangle {
                height: parent.height
                width: parent.width - title_column_width - chapter_column_width - column_spacing * 4
                color: "transparent"
                ListView {
                    id: reading_window
                    visible: true
                    model: scripture_model
                    anchors.fill: parent
                    delegate: Text {
                        id: scripture_text
                        width: parent ? parent.width : 0
                        color: font_color
                        font.pointSize: font_size
                        text: "<b>" + verse + "</b>" + " " + scripture
                        wrapMode: Text.WordWrap
                        horizontalAlignment: Text.AlignJustify
                    }
                }
                ListView {
                    id: search_window
                    visible: false
                    model: search_model
                    anchors.fill: parent
                    delegate: Text {
                        id: search_text
                        width: parent.width
                        color: font_color
                        font.pointSize: font_size
                        text: "<b>" + location + "</b>" + " " + scripture
                        wrapMode: Text.WordWrap
                        horizontalAlignment: Text.AlignJustify
                    }
                }
            }
        }

    }

}
