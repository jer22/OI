import re
import os
for fpathe,dirs,fs in os.walk(os.getcwd()):
  for f in fs:
    now = os.path.join(fpathe,f)
    if not re.compile(r'.*\.git.*').match(now) :
    	if not re.compile(r'.*\.[ciopIOCdtr].*').match(now) and not re.compile(r'.*UOJ.*').match(now) :
    		os.remove(now)
