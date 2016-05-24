import QtQuick 2.6
import QtQuick.Controls 1.2

ApplicationWindow {
    property int title_column_width: 130
    property int chapter_column_width: 40
    property int column_spacing : 5
    property int font_size: 12
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

    Books { id: books }

    Row {
        spacing: column_spacing
        width: parent.width
        height: parent.height

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
                        current_book = index + 1;
                        current_chapter = 1;
                        scripture_model.fetch(current_book, 1);
                        chapter_list.model = scripture_model.chapterCount();
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
                        current_chapter = index + 1;
                        scripture_model.fetch(current_book, current_chapter)
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
                model: scripture_model
                anchors.fill: parent
                delegate: Text {
                    id: scripture_text
                    width: parent.width
                    color: font_color
                    font.pointSize: font_size
                    text: verse + " " + scripture
                    wrapMode: Text.WordWrap
                    horizontalAlignment: Text.AlignJustify
                }
            }
        }
    }

}
