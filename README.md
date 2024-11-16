# LXC

## What is this?

Node native bindings to LXC inspired by: https://github.com/mcollina/lxc-native.

## Requirements?

### Dev Env

This is tested with Ubuntu Jammy with the following packages installed.

- build-essential
- lxc
- liblxc-dev
- nodejs (lts)

A Vagrantfile is provided to spin up a compatible environment using `vagrant up`

### Prod Env

Ubuntu Jammy is recommended and you need the following packages

- lxc
- nodejs (lts)

## Usage

### Creating a container from a template

```javascript
// set name and lxc folder
const container = new LxcContainer({
  name: "test",
  lxcPath: "/var/lib/lxc",
});

// fill in rootfs and lxc config file from a template
await container.createFromTemplate({
  distro: "ubuntu",
  release: "focal",
  arch: "arm64",
});

// start the container
await container.start();

// stop the container, time out after 30 seconds
await container.stop(30);

// destroy the container
await container.destory();
```

### List containers

```javascript
const containers = await LxcContainer.listContainers("/var/lib/lxc");
console.log(containers);
// list of names of the containers
```

### Get state of container

```javascript
const container = new LxcContainer({
  name: "test",
  lxcPath: "/var/lib/lxc",
});
const state = container.getState();
console.log(state);
// STOPPED, etc
```

## Feature Completion

- [x] Can create containers
- [x] Can start/stop containers
- [x] Can destroy containers
- [x] Can list containers
- [x] Can get container state
- [ ] Can manage running container networks
- [ ] Can fetch container logs
- [ ] Can manage container snapshots
- [ ] Can execute commands inside container
- [ ] Simplified custom lxc configuration for volume bindings etc when not creating from template\
