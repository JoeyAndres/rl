import fs from 'fs';
import _ from 'lodash';
import config from 'config';
import child_process from 'child_process';

import envInterface from '../env-interface';

let spawnSync = child_process.spawnSync;
let dependencies = config.get("test.env.linux.dependencies");

/**
 * @class linuxEnv
 *
 * Base class for linux test environment.
 */
export default class linuxEnv extends envInterface {
    constructor(options) {
        super(options);
        this.addDependencies(dependencies);
    }

    build() {
        let dockerFile = fs.readFileSync(this.getDockerFileDir() + '/Dockerfile.erb');
        let compiledTemplate =  _.template(dockerFile)({
            baseImage: this.getDockerBaseImage(),
            dependencies: this.getDependencies()
        });
        fs.writeFileSync(`${this.getDockerFileDir()}/Dockerfile`, compiledTemplate);

        spawnSync('cp', [
            '-rf',
            `${__dirname}/common/executeTest.sh`,
            this.getDockerFileDir()
        ]);

        this._buildDockerImage();
        this._pushDockerImage();
    }
}
