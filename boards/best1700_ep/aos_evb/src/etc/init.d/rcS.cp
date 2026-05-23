/****************************************************************************
 * vendor/bes/boards/best1700_ep/src/etc/init.d/rcS.cp
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/
#ifdef CONFIG_NETUTILS_REXECD
rexecd -r &
#endif

#ifdef CONFIG_BLUETOOTH_SERVER
bluetoothd &
#endif

#ifdef CONFIG_LIB_FLUORIDE

#endif /* CONFIG_LIB_FLUORIDE */

#ifdef CONFIG_LIB_BLUELET
if [ ! -d /data/nobusiness ]; then
miwear_bluetooth &
fi
#endif /* CONFIG_LIB_BLUELET */

#ifdef CONFIG_NET_LOOPBACK
ifdown lo
#endif

#ifdef CONFIG_MIWEAR_ALGORITHM_ALGOSERVICE
miwear_algo_service &
#endif

#ifdef CONFIG_SYSTEM_SETLOGMASK
if [ -d /data/logmaskr ]; then
setlogmask r &
fi
#endif
