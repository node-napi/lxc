const assert = require("assert");
const { test, before, after } = require("node:test");
const { tmpdir } = require('node:os')
const { mkdtemp,mkdir,rm } = require('node:fs/promises')
const { join } = require('node:path')
const { LxcContainer } = require("../lib/binding");

let workingDir;
let container;

before(async () => {
  workingDir = await mkdtemp(join(tmpdir(), 'lxc-'))
  await mkdir(join(workingDir, 'test'))
  // Create an instance of LxcContainer
  container = new LxcContainer({
    name: 'test',
    lxcPath: workingDir
  });
});

after(async () => {
  await rm(workingDir, {
    recursive: true,
    force: true
  })
})

test("should create an instance of LxcContainer", () => {
  assert(container instanceof LxcContainer);
});



test("should get the state of the container", () => {
  const state = container.getState();
  assert.strictEqual(typeof state, "string");
  assert.strictEqual(state, "STOPPED");
});

test("should create a container from template", async () => {
  await assert.doesNotReject(container.createFromTemplate({
    distro: 'ubuntu',
    release: 'focal',
    arch: 'arm64'
  }))
})

test("should start the container", async () => {
  await assert.doesNotReject(() => container.start());
});

test("should stop the container", async () => {
  await assert.doesNotReject(container.stop(30));
});

test("should get the state of the container after stopping", () => {
  const state = container.getState();
  assert.strictEqual(typeof state, "string");
  assert.strictEqual(state, "STOPPED"); // Assuming the state is 'STOPPED' after stop
});

test("should destroy the container", async () => {
  await assert.doesNotReject(container.destroy())
})
