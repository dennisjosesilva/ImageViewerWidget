# ImageViewerWidget

It is a minimal image viewer widget for Qt.

## Installation

It can be installed using conan, by running the following comand at the root directory of the repository:

```bash
$ conan create . ImageViewerWidget/0.0.1@dennisjosesilva/dev
```

## Usage

It can be used as any other Qt Widget. A minimal example would be:

```cpp
namespace iv = ImageViewerWidget;

iv::ImageViewerWidget* viewer = new iv::ImageViewerWidget(this);
viewer->loadImage("path/to/an/image.format");
```
