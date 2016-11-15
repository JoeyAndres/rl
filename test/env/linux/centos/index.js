import centosEnv from './centos-env';

let centosVersions = [ "7" ];

let centosEnvs = centosVersions.map(centosVersion => {
    return new centosEnv({
        baseImg: `centos:${centosVersion}`,
        dockerfileDir: `${__dirname}/${centosVersion}`
    });
});
export default centosEnvs;
