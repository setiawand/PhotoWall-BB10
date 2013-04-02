import bb.cascades 1.0
import remote.thumbnail 1.0

NavigationPane {
    id: nav
    Page {
        id: page
        property variant stag: "Indonesia"
        Container {
            background: backgroundImage.imagePaint
            layout: DockLayout {
            }
            ListView {
                id: photoList
                layout: GridListLayout {
                    id: gridLayout
                    orientation: LayoutOrientation.TopToBottom
                }
                dataModel: _photoModel
                listItemComponents: [
                    ListItemComponent {
                        type: "item"
                        RemoteThumbnailView {
                            id: photoItem
                            url: {
                                ListItemData["media:thumbnail"]["url"];
                            }
                        }
                    }
                ]
                attachedObjects: [
                    OrientationHandler {
                        id: handler
                        onOrientationChanged: {
                            if (orientation == UIOrientation.Portrait) {
                                gridLayout.columnCount = 3;
                            } else if (orientation == UIOrientation.Landscape) {
                                gridLayout.columnCount = 5;
                            }
                        }
                    }
                ]
                function itemType(data, indexPath) {
                    if (indicator.visible == true) {
                        indicator.visible = false;
                    }
                    indicator.stop();
                    return 'item';
                }
            }
            ActivityIndicator {
                id: indicator
                preferredWidth: 400
                preferredHeight: 400
                horizontalAlignment: HorizontalAlignment.Center
                verticalAlignment: VerticalAlignment.Center
            }
            animations: [
                TranslateTransition {
                    id: userInteractionDelay
                    delay: 5000
                    onEnded: {
                        page.actionBarVisibility = ChromeVisibility.Hidden
                    }
                }
            ]
            onTouch: {
                if (userInteractionDelay.isPlaying()) {
                    userInteractionDelay.stop();
                }
                userInteractionDelay.play()
                page.actionBarVisibility = ChromeVisibility.Overlay
            }
            onCreationCompleted: {
                userInteractionDelay.play()
                page.actionBarVisibility = ChromeVisibility.Overlay
            }
            attachedObjects: [
                ImagePaintDefinition {
                    id: backgroundImage
                    imageSource: "images/bgwall.jpg"
                }
            ]
        }
        actions: [
            ActionItem {
                title: "Refresh"
                ActionBar.placement: ActionBarPlacement.OnBar
                onTriggered: {
                    startIndicator();
                    app.refresh(page.stag.toString());
                }
                imageSource: "images/refresh.png"
            }
        ]
    }
    onCreationCompleted: {
        page.stag = "Indonesia";
        startIndicator();
        OrientationSupport.supportedDisplayOrientation = SupportedDisplayOrientation.All;
    }
    peekEnabled: false
    function startIndicator() {
        if (indicator.visible == false) {
            indicator.visible = true;
        }
        indicator.start();
    }
}
