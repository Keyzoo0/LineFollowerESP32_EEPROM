# Robot Line Follower ESP32
Robot line follower ini dirancang oleh Komunitas EEPROM Polinema menggunakan mikrokontroler ESP32 dual-core dan dilengkapi dengan berbagai sensor serta aktuator untuk mendeteksi garis dan menggerakkan robot. Robot ini mampu mengikuti garis, melakukan berbagai aksi, dan dapat dikonfigurasi melalui antarmuka pengguna.

# Flowchart
    Inisialisasi:
        Membaca data konfigurasi dari Memory Eksternal
        Mengkalibrasi sensor
        Menampilkan menu utama pada OLED

    Pengambilan Data:
        Membaca data dari sensor IR, MPU-9250, dan tombol
        Mengkonversi data analog dari sensor IR menjadi digital

    Pengambilan Keputusan:
        Membandingkan data sensor IR dengan nilai ambang batas untuk menentukan posisi garis
        Memproses data dari MPU-9250 untuk kontrol keseimbangan (jika ada)
        Memeriksa status tombol untuk menjalankan aksi tertentu

    Pengendalian Motor:
        Menghitung kecepatan dan arah motor berdasarkan data sensor dan keputusan yang diambil
        Mengatur driver motor (BTS7960) sesuai dengan perhitungan

    Tampilan:
        Menampilkan informasi seperti posisi robot, kecepatan, dan status pada OLED

    Aksi:
        Melakukan aksi-aksi yang telah diprogram, seperti mengikuti garis, menghindar rintangan, atau menjalankan mode tertentu

# Fitur Tambahan 

    Pengaturan:
        Mengatur kecepatan motor
        Mengatur sensitivitas sensor
        Mengatur titik kontrol
        Mengkalibrasi sensor
    Mode:
        Mode manual
        Mode otomatis
        Mode kalibrasi PID
    Penyimpanan:
        Menyimpan data konfigurasi ke Memory

# Pengembangan Lebih Lanjut

    Penambahan Fitur:
        Penambahan Fitur Transfer Plan
        Penambahan Fitur OTA (Upload Program Tanpa Kabel)  
        Penambahan Fitur Mode Transporter 
    Algoritma:
        Implementasi algoritma PID untuk kontrol motor yang lebih presisi
        Penggunaan algoritma pencarian jalur otomatis 
   
#1. Instruksi Penggunaan

    Persiapan:
        Pastikan robot telah dirakit dengan benar dan semua komponen terhubung dengan baik.
        Pastikan baterai terpasang dengan benar dan memiliki daya yang cukup.
        Hubungkan robot ke komputer melalui USB untuk mengunggah program.
    Mengunggah Program:
        Gunakan IDE seperti Arduino IDE atau Visual Studio Code untuk mengedit dan mengunggah kode program ke ESP32.
        Ikuti petunjuk pada IDE untuk memilih port serial yang benar dan mengunggah sketsa.
    Pengoperasian:
        Setelah program diunggah, hidupkan robot.
        Gunakan tombol pada robot atau antarmuka pengguna lainnya (jika ada) untuk mengontrol mode operasi.
        Letakkan robot pada garis yang akan diikuti.

#2. Troubleshooting

    Robot tidak bergerak:
        Periksa koneksi motor dan driver motor.
        Pastikan baterai memiliki daya yang cukup.
        Periksa kode program, terutama bagian yang mengatur kecepatan motor.
    Sensor tidak mendeteksi garis:
        Kalibrasi Ulang Sensor
        Bersihkan sensor IR dari debu atau kotoran.
        Periksa nilai ambang batas pada kode program.
        Pastikan garis yang digunakan memiliki kontras yang cukup dengan permukaan sekitarnya.
    Robot tidak stabil:
        Atur nilai PID untuk kontrol motor yang lebih baik.
    Program tidak dapat diunggah:
        Pastikan driver USB terpasang dengan benar.
        Periksa koneksi antara komputer dan robot.
        Coba gunakan port serial yang berbeda.

#3. Referensi

    Dokumentasi Komponen:
        - ESP32 Type-S Dual Core 240 Mhz
        - MPU-9250 Gyro Sensor 
        - BTS7960 Motor Driver
        - ADC Sensor IR Phtotodiode 
        - Motor DC 12V 1000 RPM With Encoder
