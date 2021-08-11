from conans import ConanFile, CMake, tools

class ImageViewerWidget(ConanFile):
  name = "ImageViewerWidget"
  version = "0.0.1"
  license = "<Put the package license here>"
  description = "A Morphological tree prototyping library"
  settings = "os", "compiler", "build_type", "arch"
  options = {"shared": [True, False], "compiler": ["gcc", "clang"]}
  default_options = {"shared": False, "compiler": "gcc"}
  generators = "cmake"

  def export_sources(self):
    self.copy("*.cpp", dst="src", src="src")
    self.copy("CMakeLists.txt", dst="src", src="src")
    self.copy("*.hpp", dst="include", src="include")

  def build(self):
    cmake = CMake(self)
    cmake.configure(source_folder="src")
    cmake.build()

  def package(self):
    self.copy("*.hpp", dst="include", src="include")
    self.copy("*.lib", dst="lib", keep_path=False)
    self.copy("*.dll", dst="bin", keep_path=False)
    self.copy("*.dylib", dst="lib", keep_path=False)
    self.copy("*.so", dst="lib", keep_path=False)
    self.copy("*.a", dst="lib", keep_path=False)

  def package_info(self):
    self.cpp_info.libs = ["ImageViewerWidget"]