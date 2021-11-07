# Air-Quality-KMU
- 2021 KMU 하계 현장실습 프로그램
- Support GatoLab

---

### 0. **개요**
raspberry - arduino를 활용하여 IOT환경에서 실내 공기질 센서 데이터를 측정, 수집, 관리한다.
prometheus - grafana를 연동하여 데이터를 시각화하여 실시간 모니터링 또한 가능하게 한다.
autostart와 screensaver를 활용하여 실행에 편의성을 부여한다.
시스템 과부화 및 전력소모 방지를 위해 일정 시간마다 모니터를 on/off한다.

---

### 1. 조원
```
PL  박준용
github : https://github.com/jyporse
```
```
양성민
github : https://github.com/ysmin709
```
```
이승준
github : https://github.com/ls-jun
```
---

### 2. 센서모듈
- Multichannel Gas Sensor (가스 센서)

| 측정가스 | 이름 | 범위 |
|---|---|---|
| CO |일산화탄소| 1 – 1000ppm |
| NO2 |이산화질소| 0.05 – 10ppm |
| H2 |수소| 1 – 1000ppm |
| C2H6OH |에탄올| 10 – 500ppm |
| NH3 |암모니아| 1 – 500ppm |
| C3H8 |프로페인| > 1000ppm |
| CH4 |메테인| > 1000ppm |
| C4H10 |뷰테인| > 1000ppm |

- PMS7003m    (미세먼지 센서)

| 측정종류 | 이름 | 범위 |
|---|---|---|
|PM1|극초미세먼지||
|PM2.5|초미세먼지|0~500μg/m³ (최대 ≥1000μg/m³)|
|PM10|미세먼지|

- BME280     (온도/습도/대기압 센서)

| 측정종류 | 이름 | 범위 |
|---|---|---|
|Temperature|온도|-40 - 85°C|
|Humidity|습도||
|Pressure|대기압|300 - 1100hPa|

- TG100     (co2 센서)

| 측정종류 | 이름 | 범위 |
|---|---|---|
|CO2|이산화탄소|0 - 10,000ppm|

---

### 3. 사용 스택
<img src="https://img.shields.io/badge/raspberry-A22846?style=for-the-badge&logo=RaspberryPi&logoColor=white"> <img src="https://img.shields.io/badge/Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white"> <img src="https://img.shields.io/badge/prometheus-E6522C?style=for-the-badge&logo=prometheus&logoColor=white"> <img src="https://img.shields.io/badge/grafana-F46800?style=for-the-badge&logo=grafana&logoColor=white">
<img src="https://img.shields.io/badge/python-3776AB?style=for-the-badge&logo=python&logoColor=white"> <img src="https://img.shields.io/badge/github-181717?style=for-the-badge&logo=github&logoColor=white">

---

### 4. 회로도
![회로도사진](./image/공기질_회로도.png)
![전체모습](./image/실내공기질_아두이노_.jpg)

---

### 5. 실행모습
![실행예시](./image/실행예시.png)

---
