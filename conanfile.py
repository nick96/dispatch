from conans import ConanFile, tools


class DispatchConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"
    default_options = {"zmq:encryption": "tweetnacl", "msgpack:header_only": True}
    requires = "zmq/4.3.2@bincrafters/stable", "msgpack/3.2.0@bincrafters/stable"

    def requirements(self):
        if tools.os_info.is_windows:
            self.requires("getopt/2.0@bincrafters/stable")
