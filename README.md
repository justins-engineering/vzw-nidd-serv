# Nidd Sign Server
A middleware server Docker Image based on [NGIX Unit](https://unit.nginx.org/) that transforms and exchanges data between an [IoT device](https://docs.circuitdojo.com/nrf9160-introduction.html) and Verizon Thingspace using Verizon's [ThingSpace Connectivity Management API](https://thingspace.verizon.com/documentation/apis/connectivity-management/working-with-verizon/about-non-ip-data-delivery.html).

## Development

### Recomendations
- Install [NGINX Unit from source](https://unit.nginx.org/installation/#source-code)
  - `make` libunit-install ([ref](https://www.nginx.com/blog/nginx-unit-adds-assembly-language-support/))
  - Make sure `libunit.a` and it's `include` dir are in a path that GCC includes by default; or edit the C include file paths in the [source code](https://github.com/justins-engineering/nidd-sign-serv/blob/main/src/main.c) for testing.
- VSCode
  - Build & run tasks are included
  - Configured to use Clang-Tidy
- [Docker Buildx](https://docs.docker.com/engine/reference/commandline/buildx/)

### Build
```sh
docker build -t niddss:dev .
```
- Add the docker build option `--build-arg debug=true` for debugging
  - Adds vim to the built image
  - Adds the aliases `ls='ls -F --color=auto'` & `grep='grep -nI --color=auto'` to `/root/.bashrc`
  - Builds `unitd` & `libunit.a` with the `--debug` optiion
 
### Running
```sh
docker run --rm -p 8081:8081 --name niddss_dev niddss:dev
```

### Docker image shell
```sh
docker exec -it niddss_dev /bin/bash
```
