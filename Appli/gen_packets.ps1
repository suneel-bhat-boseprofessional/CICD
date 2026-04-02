function Get-CRC16CCITT {
    param([byte[]]$data)
    [uint16]$crc = 0xFFFF
    foreach ($b in $data) {
        $crc = $crc -bxor ([uint16]$b -shl 8)
        for ($i = 0; $i -lt 8; $i++) {
            if ($crc -band 0x8000) {
                $crc = (($crc -shl 1) -bxor 0x1021) -band 0xFFFF
            } else {
                $crc = ($crc -shl 1) -band 0xFFFF
            }
        }
    }
    return $crc
}

function Build-Pkt {
    param([string]$name, [byte[]]$sof, [string]$ps)
    $p = if ($ps -eq '') { [byte[]]@() } else { [System.Text.Encoding]::ASCII.GetBytes($ps) }
    [byte]$len = $p.Length
    $cd = [byte[]](@($len) + $p)
    $crc = Get-CRC16CCITT $cd
    $cL = [byte]($crc -band 0xFF)
    $cH = [byte](($crc -shr 8) -band 0xFF)
    $pkt = [byte[]]($sof + @($cL, $cH, $len) + $p)
    $h = ($pkt | ForEach-Object { '{0:X2}' -f $_ }) -join ' '
    Write-Host "$name"
    Write-Host "  Payload: $ps"
    Write-Host "  Docklight: $h"
    Write-Host ""
    return ,$pkt
}

$N = [byte[]]@(0xA2, 0xB2, 0xC2, 0xD2)
$O = [byte[]]@(0xA1, 0xB1, 0xC1, 0xD1)

Write-Host "============================================================"
Write-Host "DOCKLIGHT TEST MESSAGES (SOF: A2 B2 C2 D2 / A1 B1 C1 D1)"
Write-Host "============================================================"
Write-Host ""

Build-Pkt "1. ready" $N '{"action":"ready"}' | Out-Null
Build-Pkt "2. setFanSpeed LOW" $N '{"action":"setFanSpeed","payload":{"speed":"LOW"}}' | Out-Null
Build-Pkt "3. setGain zone0 norm50" $N '{"action":"setGain","payload":{"zone":0,"norm":50}}' | Out-Null
Build-Pkt "4. setMute zone0 true" $N '{"action":"setMute","payload":{"zone":0,"state":"true"}}' | Out-Null
Build-Pkt "5. OTA empty payload" $O '' | Out-Null
Build-Pkt "6. OTA with payload" $O 'OTA_START' | Out-Null

# Bad CRC
Write-Host "--- Negative Tests ---"
Write-Host ""
$good = Build-Pkt "(base)" $N '{"action":"ready"}'
$bad = [byte[]]$good.Clone()
$bad[4] = $bad[4] -bxor 0xFF
$h = ($bad | ForEach-Object { '{0:X2}' -f $_ }) -join ' '
Write-Host "7. Bad CRC (expect NACK)"
Write-Host "  Docklight: $h"
Write-Host ""

$badSof = [byte[]]@(0xAA, 0xBB, 0xCC, 0xDD) + [byte[]]$good[4..($good.Length-1)]
$h = ($badSof | ForEach-Object { '{0:X2}' -f $_ }) -join ' '
Write-Host "8. Bad SOF (expect NACK)"
Write-Host "  Docklight: $h"
