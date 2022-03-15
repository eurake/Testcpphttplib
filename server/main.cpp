#include <direct.h>
#include <httplib.h>

#include <fstream>
#include <iostream>
#include <json.hpp>
#include <string>

using namespace httplib;


int main(void) {
  // 
  char buffer[256];
  char* val = getcwd(buffer, sizeof(buffer));
  const std::string rootPath(buffer);
  std::cout << rootPath << std::endl;

  // 
  Server svr;
  svr.Post("/api/v1/uploadFile", [](const Request& req, Response& res) {
    auto imgFile = req.get_file_value("imgFile");
    // console log
    std::cout << "file.filename: " << imgFile.filename << std::endl;
    std::cout << "file.content_type: " << imgFile.content_type << std::endl;
    std::cout << "file.name: " << imgFile.name << std::endl;
    std::cout << "file.content: " << imgFile.content.length() << std::endl;

    nlohmann::json jRes;
    jRes["error_code"] = -1;
    jRes["error_message"] = "file name is null fail 失败";  //
    if (imgFile.filename.length() > 0) {
        std::string imgPath = "./" + imgFile.filename;
        std::ofstream fStream(imgPath, std::ios::binary);
        fStream << imgFile.content;
        fStream.close();
        jRes["error_code"] = 0;
        jRes["error_message"] = "success 成功";  // unicode

    }
    res.set_content(jRes.dump(), "application/json");
  });

  svr.listen("localhost", 12346);
}