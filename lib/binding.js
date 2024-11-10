const NodeLxcNative = require('../build/Release/node-lxc-native-native.node')

/**
 * @typedef {Object} AttachOptions
 * @property {number} [attachFlags] - Flags to control the attach behavior.
 * @property {number} [namespaces] - Namespaces to be used.
 * @property {number} [personality] - Personality to be set.
 * @property {string} [initialCwd] - Initial working directory.
 * @property {number} [uid] - User ID to be set.
 * @property {number} [gid] - Group ID to be set.
 * @property {number} [envPolicy] - Environment policy to be set.
 * @property {string[]} [extraEnvVars] - Extra environment variables.
 * @property {string[]} [extraKeepEnv] - Extra environment variables to keep.
 * @property {number} [stdinFd] - File descriptor for standard input.
 * @property {number} [stdoutFd] - File descriptor for standard output.
 * @property {number} [stderrFd] - File descriptor for standard error.
 * @property {number} [logFd] - File descriptor for logging.
 * @property {string} [lsmLabel] - LSM (Linux Security Module) label.
 * @property {number[]} [groups] - Array of group IDs.
 */

/**
 * @typedef {Object} CreateFromTemplateOpts
 * @property {string} distro
 * @property {string} release
 * @property {string} arch
 */

class LxcContainer {
  #lxcPath
  #name
  #innerInstance

  constructor (opts) {
    this.#lxcPath = opts.lxcPath
    this.#name = opts.name
    this.#innerInstance = new NodeLxcNative.LxcContainer({
      name: this.#name,
      lxcPath: this.#lxcPath
    })
  }

  /**
   * Runs a command and waits for it to finish.
   *
   * @function
   * @name runWait
   * @memberof LxcContainer
   * @param {Object} params - The parameters for the program to run in the container.
   * @param {string} params.program - The program to run.
   * @param {string[]} params.argv - The arguments to provide to the command/program.
   * @param {AttachOptions} params.options - The attach options.
   * @returns {Promise<number>}
   */
  runWait (params) {
    return this.#innerInstance.runWait(params)
  }

  /**
   * Queries the console output of the LXC container.
   *
   * @function
   * @name queryConsole
   * @returns {Promise<string>} - The console output.
   */
  queryConsole () {
    return this.#innerInstance.queryConsole()
  }

  /**
   * Gets the network interfaces of the LXC container.
   *
   * @function
   * @name getInterfaces
   * @returns {Promise<string[]>} - An array of network interfaces.
   */
  getInterfaces () {
    return this.#innerInstance.getInterfaces()
  }

  /**
   * Gets the IP addresses of the LXC container.
   *
   * @function
   * @name getIps
   * @param {string} interfaceName
   * @param {string} family
   * @param {number?} scope
   * @returns {Promise<string[]>} - An array of IP addresses.
   */
  getIps (interfaceName, family, scope) {
    return this.#innerInstance.getIps(interfaceName, family, scope)
  }

  /**
   * Gets the PID of the LXC container.
   *
   * @function
   * @name getPid
   * @returns {Promise<number>} - The PID of the container.
   */
  getPid () {
    return this.#innerInstance.getPid()
  }

  /**
   * Reboots the LXC container.
   *
   * @function
   * @name reboot
   * @param {number} timeoutSeconds
   * @returns {Promise<void>}
   */
  reboot (timeoutSeconds) {
    return this.#innerInstance.reboot(timeoutSeconds)
  }

  /**
   * Shuts down the LXC container.
   *
   * @function
   * @name shutdown
   * @param {number} timeoutSeconds
   * @returns {Promise<void>}
   */
  shutdown (timeoutSeconds) {
    return this.#innerInstance.shutdown(timeoutSeconds)
  }

  /**
   * Destroys the LXC container.
   *
   * @function
   * @name destroy
   * @returns {Promise<void>}
   */
  destroy () {
    return this.#innerInstance.destroy()
  }

  /**
   * Waits for the LXC container to reach a specific state.
   *
   * @function
   * @name waitForState
   * @param {string} state - The state to wait for.
   * @param {number} timeSeconds - The time to wait for the container to enter the state
   * @returns {Promise<void>}
   */
  waitForState (state, timeoutSeconds) {
    return this.#innerInstance.waitForState(state, timeoutSeconds)
  }

  /**
   * Gets the state of the LXC container.
   *
   * @function
   * @name getState
   * @returns {Promise<string>} - The state of the container.
   */
  getState () {
    return this.#innerInstance.getState()
  }

  /**
   * Creates an LXC container from a template.
   *
   * @function
   * @name createFromTemplate
   * @memberof LxcContainer
   * @param {CreateFromTemplateOpts} opts
   * @returns {Promise<void>}
   */
  createFromTemplate (opts) {
    return this.#innerInstance.createFromTemplate(opts)
  }

  /**
   * Stops the LXC container.
   *
   * @function
   * @name stop
   * @param {number} timeoutSeconds
   * @returns {Promise<void>}
   */
  stop (timeoutSeconds) {
    return this.#innerInstance.stop(timeoutSeconds)
  }

  /**
   * Starts the LXC container.
   *
   * @function
   * @name start
   * @returns {Promise<void>}
   */
  start () {
    return this.#innerInstance.start()
  }

  /**
   * Lists all LXC containers.
   *
   * @function
   * @name listContainers
   * @param {string} lxcPath
   * @static
   * @returns {Promise<string[]>} - An array of container names.
   */
  static listContainers (lxcPath) {
    return NodeLxcNative.LxcContainer.listContainers(lxcPath)
  }
}

module.exports = {
  LxcContainer
}
