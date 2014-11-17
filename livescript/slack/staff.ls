#!/usr/bin/env lsc
require! {
  'slack-node': Slack
}

slack = new Slack \xxxx-0000000000-0000000000-0000000000-xxxxxx
known = <[
  hcchien
  ETBlue
  toby
  clkao
  au
  ipa
  jimmy
  ttcat
  acechen
  lora
  bryan
  idril
  choupi
  snake
  nfs
  高照明老師
  shiashia/蝦蝦
  twpaddy
  chihyun-Tseng
  joey-Lee
  Emily
  airos
  Marie-Chang
  冰牙
  ipa
  tuiry
  miaoski
  AliceWei
  caasi/caasih
  JoeWang
  opop
  roger_____
  SLMT
  stardog
  swem
  tuiry
  張智傑
  solring
  洪民翰
  蒲郁文
  jbytw
  洪健洲
  a0kman
  ballII
  mousems
  Juanna
  薛琇文
  ch0upi_bsd
  crys_jheng
  goodfifagun
  madarame
  凌子軒
  陳潔寧
  mindos
  羅永欣/sig
  luxun
  曾群展
  pipi
  amiboshi0717
  ken
  shuhua
  楊安傑/angelboy
  Lee1092
  AceChen
  tkirby
  hazel
  daniel/丹丹
  simon/丞相
  cyj/西歪街
  ymow/阿毛
  蔡祖閩
  音地大帝
  isabel/isabelhou
  David-Huang
  波卡/Poka
  fumi
  lanf0n
  rschiang
  Erin
]>
known.sort!
known =
  for names in known
    for name in names.split '/'
      name.replace '-' -> ' '
#console.log "total: #{known.length}"
#console.log known
for name in known
  console.log name.join '/'
process.exit 0

err, res <- slack.api 'groups.list'
throw err if err
throw new Error res.error unless res.ok
#console.log res.groups.0.name
{ members } = res.groups.0
staff = []
count = 0
for id in members
  err, res <- slack.api 'users.info' user: id
  throw err if err
  throw new Error res.error unless res.ok
  staff.push do
    name: res.user.name
    realname: res.user.profile.real_name
  if ++count is members.length
    missing = []
    for let alias in known
      found = false
      :search
        for name in alias
          for member in staff
            re = new RegExp member.name.toLowerCase!, \i
            found = re.test name
            member.alias = alias
            break search if found
      missing.push alias if not found
    console.log "missing: #{missing.length}"
    for alias in missing
      console.log alias.join '/'
    #for member in staff
    #  console.log "#{member.name} #{member?alias?join '/' or ''}"

