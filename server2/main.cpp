
#include <httplib.h>

#include <fstream>
#include <iostream>
#include <json.hpp>
#include <string>
using namespace httplib;
using namespace std;

const char *html = R"(
<form id="formElem">
  <input type="file" name="image_file" accept="image/*">
  <input type="file" name="text_file" accept="text/*">
  <input type="submit">
</form>
<script>
  formElem.onsubmit = async (e) => {
    e.preventDefault();
    let res = await fetch('/post', {
      method: 'POST',
      body: new FormData(formElem)
    });
    console.log(await res.text());
  };
</script>
)";

int main(void) {
  Server svr;

  svr.Get("/", [](const Request & /*req*/, Response &res) {
    res.set_content(html, "text/html");
  });

  svr.Post("/post", [](const Request &req, Response &res) {
    auto image_file = req.get_file_value("image_file");
    auto text_file = req.get_file_value("text_file");

    cout << "image file length: " << image_file.content.length() << endl
         << "image file name: " << image_file.filename << endl
         << "text file length: " << text_file.content.length() << endl
         << "text file name: " << text_file.filename << endl;

    {
      ofstream ofs(image_file.filename, ios::binary);
      ofs << image_file.content;
    }
    {
      ofstream ofs(text_file.filename);
      ofs << text_file.content;
    }

    res.set_content("done", "text/plain");
  });

  svr.Post("/downloadExcel", [](const Request& req, Response& res) {
      // Step 1 Processing request parameters and  create excel file  and save
      // std::string  req.get_param_value("name");
      // std::string req.get_param_value("startDate");
      // std::string req.get_param_value("endDate");

      // Step2 Open read to data buffer
      std::cout << "hrer " << std::endl;
      std::filebuf* pbuf;
      std::ifstream filestr;
      long size;
      char* data;
      filestr.open("./test2.xlsx", std::ios::binary);
      pbuf = filestr.rdbuf();
      size = pbuf->pubseekoff(0, std::ios::end, std::ios::in);
      pbuf->pubseekpos(0, std::ios::in);
      data = new char[size];
      pbuf->sgetn(data, size);
      filestr.close();
      std::cout.write(data, size);

       std::cout << "hrer 2" << std::endl;

      res.set_header("Content-Disposition", "attachment; filename=file.xls");
      res.set_content_provider(
          size, "application/xslt+xml",
          [data](size_t offset, size_t length, DataSink& sink) {
              size_t DATA_CHUNK_SIZE = 1024;
              const auto d = data;
              auto out_len = std::min(static_cast<size_t>(length), DATA_CHUNK_SIZE);
              auto ret = sink.write(&d[offset], out_len);
              return true;
          },
          [data](bool success) { delete data; });
      });
  svr.listen("127.0.0.1", 12346);
}