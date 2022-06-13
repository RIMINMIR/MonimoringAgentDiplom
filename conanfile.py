from conans import ConanFile, CMake


class MonitoringAgent(ConanFile):
    name = "main"
    version = "1.0"
    settings = "os", "compiler", "arch"
    options = {"shared": [True, False]}
    #default_options = "shared=False"
    generators = "cmake"
    exports_sources = "src/*"
    requires = (
        "fmt/6.1.2",
        "nlohmann_json/3.10.5",
        "gtest/1.11.0",
        'zlib/1.2.12',
        'sqlite3/3.38.1',
        'soci/4.0.3',
        'thrift/0.15.0'
    )
    default_options = {"soci:with_sqlite3": True, "shared": False}

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        if self.settings.os == "Windows":
            self.copy("*.exe", dst = "bin", src = "bin")
            self.copy("*.dll", dst = "bin", src = "bin")
            self.copy("*.lib", dst = "lib", src = "lib")