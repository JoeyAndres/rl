import ubuntuEnv from './ubuntu-env';

let ubuntuVersions = [
    "14.04",
    "15.04",
    "15.10",
    "16.04",
    "16.10"
];

let ubuntuEnvs = ubuntuVersions.map(ubuntuVersion => {
    return new ubuntuEnv({
        baseImg: `ubuntu:${ubuntuVersion}`,
        dockerfileDir: `${__dirname}/${ubuntuVersion}`
    });
});
export default ubuntuEnvs;
