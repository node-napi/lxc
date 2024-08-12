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
 * LxcContainer provides bindings for LXC container management.
 *
 * @typedef {Object} LxcContainer
 */

/**
 * Creates an LXC container from a template.
 *
 * @function
 * @name createFromTemplate
 * @memberof LxcContainer
 * @param {string} templateName - The name of the template to use.
 * @param {string} containerName - The name of the container to create.
 * @returns {Promise<void>}
 */

/**
 * Starts the LXC container.
 *
 * @function
 * @name start
 * @memberof LxcContainer
 * @returns {Promise<void>}
 */

/**
 * Stops the LXC container.
 *
 * @function
 * @name stop
 * @memberof LxcContainer
 * @returns {Promise<void>}
 */

/**
 * Destroys the LXC container.
 *
 * @function
 * @name destroy
 * @memberof LxcContainer
 * @returns {Promise<void>}
 */

/**
 * Gets the state of the LXC container.
 *
 * @function
 * @name getState
 * @memberof LxcContainer
 * @returns {Promise<string>} - The state of the container.
 */

/**
 * Gets the PID of the LXC container.
 *
 * @function
 * @name getPid
 * @memberof LxcContainer
 * @returns {Promise<number>} - The PID of the container.
 */

/**
 * Reboots the LXC container.
 *
 * @function
 * @name reboot
 * @memberof LxcContainer
 * @returns {Promise<void>}
 */

/**
 * Shuts down the LXC container.
 *
 * @function
 * @name shutdown
 * @memberof LxcContainer
 * @returns {Promise<void>}
 */

/**
 * Gets the IP addresses of the LXC container.
 *
 * @function
 * @name getIps
 * @memberof LxcContainer
 * @instance
 * @returns {Promise<string[]>} - An array of IP addresses.
 */

/**
 * Gets the network interfaces of the LXC container.
 *
 * @function
 * @name getInterfaces
 * @memberof LxcContainer
 * @returns {Promise<string[]>} - An array of network interfaces.
 */

/**
 * Queries the console output of the LXC container.
 *
 * @function
 * @name queryConsole
 * @memberof LxcContainer
 * @returns {Promise<string>} - The console output.
 */

/**
 * Waits for the LXC container to reach a specific state.
 *
 * @function
 * @name waitForState
 * @memberof LxcContainer
 * @param {string} state - The state to wait for.
 * @returns {Promise<void>}
 */

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

/**
 * Lists all LXC containers.
 *
 * @function
 * @name listContainers
 * @memberof LxcContainer
 * @static
 * @returns {Promise<string[]>} - An array of container names.
 */

/** @type {LxcContainer} */
const LxcContainer = NodeLxcNative.LxcContainer

module.exports = {
  /**
   * @type {LxcContainer}
   */
  LxcContainer
}
