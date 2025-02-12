# Webserver

This project is a simple web server implementation. It is designed to handle HTTP requests and serve static files, as well as execute CGI scripts. The server is configured using a configuration file (`webserv.conf`).

## Features

* Handles HTTP requests and responses
* Serves static files from a specified root directory
* Supports CGI scripts for dynamic content generation
* Configurable using a `webserv.conf` file
* Supports multiple virtual hosts
* Customizable error pages
* Autoindexing for directories

## Configuration

The server is configured using the `webserv.conf` file. This file allows you to define virtual hosts, set root directories, enable CGI scripts, and configure error pages. Here is an example configuration:

```conf
server {
    listen 8080;
    server_name www.example.com;

    location / {
        root /var/www/html;
        autoindex on;
        cgi_path .pl /usr/bin/perl;
        allow POST GET;
        index index.pl;
    }
}
```

## Directory Structure

* `html/` - Contains HTML files for error pages and static content
* `html/site/perl/` - Contains Perl CGI scripts
* `html/site/php/` - Contains PHP scripts
* `include/` - Header files for the project
* `src/` - Source code for the project
* `webserv.conf` - Configuration file for the web server

## Building and Running

To build the project, use the provided `Makefile`:

```sh
make
```

To run the server, execute the generated binary:

```sh
./webserv
```

## License

This project is licensed under the GNU General Public License v3.0. See the `LICENSE` file for more details.
