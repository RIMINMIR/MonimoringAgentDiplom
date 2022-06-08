from conans import ConanFile, CMake


class HelloConan(ConanFile):
    name = "main"
    version = "1.0"
    settings = "os", "compiler", "arch"
    options = {"shared": [True, False]}
    default_options = "shared=False"
    generators = "cmake"
    exports_sources = "src/*"
    requires = (
        "boost/1.72.0",
        "fmt/6.1.2",
        "rapidjson/1.1.0",
        "gtest/1.11.0",
        "poco/1.11.1",
        'zlib/1.2.12',
        'sqlite3/3.38.1',
        'soci/4.0.2'
    )

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        if self.settings.os == "Windows":
            self.copy("*.exe", dst = "bin", src = "bin")
            self.copy("*.dll", dst = "bin", src = "bin")
            self.copy("*.lib", dst = "lib", src = "lib")