import _ from 'lodash';

import ubuntuEnvs from './ubuntu';
import centosEnvs from './centos';

let linuxEnvs = _.concat(ubuntuEnvs, centosEnvs);
export default linuxEnvs;
