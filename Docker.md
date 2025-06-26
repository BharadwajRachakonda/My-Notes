# Docker

## What is docker and what is a container?

> A container is a way to package application with all the necessary dependencies and configuration.

> It is a Portable artifact, easily shared and moved around.

> This makes development and deployment process more efficient.

### Where do containers live or stored?

> Containers live in a container repository, it is a special type of storage for containers.

> A container repository can be private to a company or public.

> docker hub is the dockers public repository.

> For every type of application docker has a container image.

- In genreal to develop a application you first install the dependencies and configurations.

- And the installation process differs with the operating system.

- so setting up a new environment is tedious

> With containers there is no need to download any of the services in our operating system as the container has its own isolated operating system.

> No matter what operating system you are using the docker command to start the application won't change.

> you can run different versions of same application running on you local environment without any conflict.

> Developer and operations work together ro package the application in a container.

> No environmental configuration needed on server - except Docker Runtime

> All you need to do is to run a doccker command that pulls the doceker image.
