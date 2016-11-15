import gulp from 'gulp';

import {envs} from './test';

gulp.task('build-test-env', () => {
    envs.forEach(env => env.build());
});
