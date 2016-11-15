import config from 'config';

import linuxEnv from '../linux-env';

let dependencies = config.get("test.env.linux.ubuntu.dependencies");

export default class ubuntuEnv extends linuxEnv {
    constructor(options) {
        super(options);
        this.addDependencies(dependencies);
    }
}
