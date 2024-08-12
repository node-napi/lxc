const assert = require('assert')
const { test, before, after } = require('node:test')
const { tmpdir } = require('node:os')
const { mkdtemp, mkdir, rm } = require('node:fs/promises')
const { join } = require('node:path')
const { LxcContainer } = require('../lib/binding')

let workingDir
let container

before(async () => {
  workingDir = await mkdtemp(join(tmpdir(), 'lxc-'))
  await mkdir(join(workingDir, 'test'))
  // Create an instance of LxcContainer
  container = new LxcContainer({
    name: 'test',
    lxcPath: workingDir
  })
})

after(async () => {
  await rm(workingDir, {
    recursive: true,
    force: true
  })
})

test('should create an instance of LxcContainer', () => {
  assert(container instanceof LxcContainer)
})

test('should get the state of the container', () => {
  const state = container.getState()
  assert.strictEqual(typeof state, 'string')
  assert.strictEqual(state, 'STOPPED')
})

test('should create a container from template', async () => {
  await assert.doesNotReject(
    container.createFromTemplate({
      distro: 'ubuntu',
      release: 'focal',
      arch: 'arm64'
    })
  )
})

test('should start the container', async () => {
  await assert.doesNotReject(() => container.start())
})

test('should wait for the container to be ready', async () => {
  await assert.doesNotReject(
    container.waitForState({
      state: 'RUNNING',
      timeoutSeconds: 30
    })
  )
})

test('should timeout for bad state', async () => {
  await assert.rejects(
    container.waitForState({
      state: 'STOPPED',
      timeoutSeconds: 2
    })
  )
})

test('should include the container in the list', async () => {
  const containers = await LxcContainer.listContainers(workingDir)
  assert.ok(containers != null, 'must provide a result')
  assert.ok(Array.isArray(containers), 'must provide an array')
  assert.ok(containers.length > 0, 'must provide a list greater than 0')
  assert.ok(
    containers.some((c) => c === 'test'),
    'must have the container we started'
  )
})

test('should provide the ip addresses', async () => {
  const interfaces = await container.getInterfaces()
  assert.ok(interfaces != null, 'must return a list of interfaces')
  assert.ok(interfaces.length > 0, 'must have interfaces in the list')
  for (const iface of interfaces) {
    const result = await container.getIps(iface, 'inet')
    assert.ok(result != null, 'must return a result')
  }
})

test('should query the console logs', async () => {
  const logs = await container.queryConsole(500)
  assert.ok(logs != null, 'must provide a value')
  assert.ok(typeof logs === 'string', 'must provide a string')
  assert.ok(logs.length > 0, 'must provide log content')
})

test('should stop the container', async () => {
  await assert.doesNotReject(container.stop(30))
})

test('should get the state of the container after stopping', () => {
  const state = container.getState()
  assert.strictEqual(typeof state, 'string')
  assert.strictEqual(state, 'STOPPED') // Assuming the state is 'STOPPED' after stop
})

test('should destroy the container', async () => {
  await assert.doesNotReject(container.destroy())
})
