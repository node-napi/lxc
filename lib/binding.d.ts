export type AttachOptions = {
  /**
   * - Flags to control the attach behavior.
   */
  attachFlags?: number;
  /**
   * - Namespaces to be used.
   */
  namespaces?: number;
  /**
   * - Personality to be set.
   */
  personality?: number;
  /**
   * - Initial working directory.
   */
  initialCwd?: string;
  /**
   * - User ID to be set.
   */
  uid?: number;
  /**
   * - Group ID to be set.
   */
  gid?: number;
  /**
   * - Environment policy to be set.
   */
  envPolicy?: number;
  /**
   * - Extra environment variables.
   */
  extraEnvVars?: string[];
  /**
   * - Extra environment variables to keep.
   */
  extraKeepEnv?: string[];
  /**
   * - File descriptor for standard input.
   */
  stdinFd?: number;
  /**
   * - File descriptor for standard output.
   */
  stdoutFd?: number;
  /**
   * - File descriptor for standard error.
   */
  stderrFd?: number;
  /**
   * - File descriptor for logging.
   */
  logFd?: number;
  /**
   * - LSM (Linux Security Module) label.
   */
  lsmLabel?: string;
  /**
   * - Array of group IDs.
   */
  groups?: number[];
};
export type CreateFromTemplateOpts = {
  distro: string;
  release: string;
  arch: string;
};
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
export class LxcContainer {
  /**
   * Lists all LXC containers.
   *
   * @function
   * @name listContainers
   * @param {string} lxcPath
   * @static
   * @returns {Promise<string[]>} - An array of container names.
   */
  static listContainers(lxcPath: string): Promise<string[]>;
  constructor(opts: any);
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
  runWait(params: {
    program: string;
    argv: string[];
    options: AttachOptions;
  }): Promise<number>;
  /**
   * Queries the console output of the LXC container.
   *
   * @function
   * @name queryConsole
   * @returns {Promise<string>} - The console output.
   */
  queryConsole(): Promise<string>;
  /**
   * Gets the network interfaces of the LXC container.
   *
   * @function
   * @name getInterfaces
   * @returns {Promise<string[]>} - An array of network interfaces.
   */
  getInterfaces(): Promise<string[]>;
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
  getIps(
    interfaceName: string,
    family: string,
    scope: number | null,
  ): Promise<string[]>;
  /**
   * Gets the PID of the LXC container.
   *
   * @function
   * @name getPid
   * @returns {Promise<number>} - The PID of the container.
   */
  getPid(): Promise<number>;
  /**
   * Reboots the LXC container.
   *
   * @function
   * @name reboot
   * @param {number} timeoutSeconds
   * @returns {Promise<void>}
   */
  reboot(timeoutSeconds: number): Promise<void>;
  /**
   * Shuts down the LXC container.
   *
   * @function
   * @name shutdown
   * @param {number} timeoutSeconds
   * @returns {Promise<void>}
   */
  shutdown(timeoutSeconds: number): Promise<void>;
  /**
   * Destroys the LXC container.
   *
   * @function
   * @name destroy
   * @returns {Promise<void>}
   */
  destroy(): Promise<void>;
  /**
   * Waits for the LXC container to reach a specific state.
   *
   * @function
   * @name waitForState
   * @param {string} state - The state to wait for.
   * @param {number} timeSeconds - The time to wait for the container to enter the state
   * @returns {Promise<void>}
   */
  waitForState(state: string, timeoutSeconds: any): Promise<void>;
  /**
   * Gets the state of the LXC container.
   *
   * @function
   * @name getState
   * @returns {Promise<string>} - The state of the container.
   */
  getState(): Promise<string>;
  /**
   * Creates an LXC container from a template.
   *
   * @function
   * @name createFromTemplate
   * @memberof LxcContainer
   * @param {CreateFromTemplateOpts} opts
   * @returns {Promise<void>}
   */
  createFromTemplate(opts: CreateFromTemplateOpts): Promise<void>;
  /**
   * Stops the LXC container.
   *
   * @function
   * @name stop
   * @param {number} timeoutSeconds
   * @returns {Promise<void>}
   */
  stop(timeoutSeconds: number): Promise<void>;
  /**
   * Starts the LXC container.
   *
   * @function
   * @name start
   * @returns {Promise<void>}
   */
  start(): Promise<void>;
  #private;
}
