import assert from 'assert';
import _ from 'lodash';
import config from 'config';
import child_process from 'child_process';

let spawnSync = child_process.spawnSync;

/**
 * @class envInterface
 *
 * This is the base class for all test environments.
 */
export default class envInterface {
    constructor(options) {
        this._dependencies = options.dependencies || [];
        this._baseImg = options.baseImg;
        this._dockerfileDir = options.dockerfileDir;
    }

    build() {
        throw "Throw not implemented";
    }

    addDependencies(dependency) {
        if (_.isString(dependency)) {
            this._dependencies.push(dependency);
        } else if (_.isArray(dependency)) {
            this._dependencies = this._dependencies.concat(dependency);
        } else {
            throw "Given dependency should be string or array";
        }
    }

    getDependencies() {
        return this._dependencies;
    }

    getDockerBaseImage() {
        if (_.isNull(this._baseImg)) {
            throw "this.name is not set.";
        }

        return this._baseImg;
    }

    getDockerImageName() {
        return `rl-env-${this.getDockerBaseImage()}`;
    }

    getDockerFileDir() {
        if (_.isNull(this._dockerfileDir)) {
            throw "this.dockerfileDir is not set";
        }
        return this._dockerfileDir;
    }

    _getDockerImageName() {
        return `${config.get('docker.user')}/${this.getDockerImageName()}`;
    }

    _buildDockerImage() {
        let result = spawnSync('docker', [
            'build',
            '-t',  this._getDockerImageName(),
            this.getDockerFileDir()
        ],  {
            stdio:[0,1,2]  // Display to the parent's stream.
        });

        if (result.error) {
            throw result.error;
        }
    }

    _pushDockerImage() {
        let result = spawnSync('docker', [
            'push', this._getDockerImageName()
        ],  {
            stdio:[0,1,2]  // Display to the parent's stream.
        });

        if (result.error) {
            throw result.error;
        }
    }
}
