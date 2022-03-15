package main

import (
	"errors"
	"fmt"
	"os"
	"os/exec"
	"path"
	"path/filepath"
	"runtime"
	"strings"

	"github.com/gin-gonic/gin"
)

func main() {
	router := gin.Default()

	// For each matched request Context will hold the route definition
	router.POST("/api/v1/uploadFile", func(c *gin.Context) {
		f, err := c.FormFile("imgFile")
		if err != nil {
			fmt.Println("error get imgFile")
			return
		}
		fileExt := strings.ToLower(path.Ext(f.Filename))
		if fileExt != ".png" && fileExt != ".jpg" && fileExt != ".gif" && fileExt != ".jpeg" {
			c.JSON(200, gin.H{
				"code": 400,
				"msg":  "上传失败!只允许png,jpg,gif,jpeg文件",
			})
			return
		}
		filePath := path.Join("./", f.Filename)
		fmt.Println("filepath", filePath)
		c.SaveUploadedFile(f, filePath)
		c.JSON(200, gin.H{
			"code": 200,
			"msg":  "上传成功!",
		})
	})

	router.Run(":12347")
}

func GetCurrentPath() (string, error) {
	file, err := exec.LookPath(os.Args[0])
	if err != nil {
		return "", err
	}
	path, err := filepath.Abs(file)
	if err != nil {
		return "", err
	}
	//fmt.Println("path111:", path)
	if runtime.GOOS == "windows" {
		path = strings.Replace(path, "\\", "/", -1)
	}
	//fmt.Println("path222:", path)
	i := strings.LastIndex(path, "/")
	if i < 0 {
		return "", errors.New(`Can't find "/" or "\".`)
	}
	//fmt.Println("path333:", path)
	return string(path[0 : i+1]), nil
}
