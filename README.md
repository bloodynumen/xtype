# xtype

获取文件类型的PHP扩展

## install

### 编译
```
git https://github.com/bloodynumen/xtype.git
phpize
/configue --with-php-config=your_php_config_path
make && make install
```

### 配置php.ini
```
extension=xtype.so
```

## 使用
```
$ext = xtype('/tmp/1.jpg')
echo $ext;
```