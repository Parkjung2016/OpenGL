#ifndef __COMMON_H__
#define __COMMON_H__

#include <memory>
#include <string>
#include <optional>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#define CLASS_PTR(className) \
class className; \
using className ## UPtr = std::unique_ptr<className>; \
using className ## Ptr = std::shared_ptr<className>; \
using classname ## WPtr = std::weak_ptr<className>;

std::optional<std::string> LoadTextFile(const std::string& filename);

#endif // __COMMON_H__
