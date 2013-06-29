/**
 * @project Andromeda
 * @author Vitaliy Krutko
 * @email asmxforce@gmail.com
**/

// mbs - main boot sector
.equ mbsADDRESS, 0x7C00
.equ mbsSEGMENT, (mbsADDRESS / 0x10)

// mpt - main partition table
.equ mptOFFSET, 0x1BE

// mbs signature
.equ mbsSIGNATURE, 0xAA55

// 512 bytes
.equ mbsSIZE, 0x200




// descriptor size
.equ dscSIZE, 0x08

// interrupt descriptor table
.equ idtADDRESS, 0x500
.equ idtSEGMENT, (idtADDRESS / 0x10)

.equ idtENTRIES, 0x100
.equ idtSIZE, (idtENTRIES * dscSIZE)
.equ idtLIMIT, (idtSIZE - 1)

// global descriptor table
.equ gdtADDRESS, (idtADDRESS + idtSIZE)
.equ gdtSEGMENT, (gdtADDRESS / 0x10)

.equ gdtENTRIES, 0x100
.equ gdtSIZE, (gdtENTRIES * dscSIZE)
.equ gdtLIMIT, (gdtSIZE - 1)




// rms - real-mode setup
.equ rmsADDRESS, (gdtADDRESS + gdtSIZE)
.equ rmsSEGMENT, (rmsADDRESS / 0x10)

// rms signature
.equ rmsSIGNATURE, mbsSIGNATURE

// 1024 bytes
.equ rmsSIZE, 0x400

// pms - protected-mode setup
.equ pmsADDRESS, (rmsADDRESS + rmsSIZE)
.equ pmsSEGMENT, (pmsADDRESS / 0x10)




// system GDT entries - null, code, data
.equ gdtSYSENTRIES, 3
.equ codeSELECTOR, (0x01 << 3)
.equ dataSELECTOR, (0x02 << 3)




// system location
.equ sysADDRESS, rmsADDRESS
.equ sysSEGMENT, rmsSEGMENT
