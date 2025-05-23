import argparse
import itertools
import sys

def verificar_clave(clave, verbose=False):
    suma = 0
    if verbose:
        print("\nDesglose de la verificación:")
        
    for i, c in enumerate(clave):
        operacion = ord(c) ^ (85 + i)
        suma += operacion
        if verbose:
            print(f"Carácter {i + 1}: '{c}'")
            print(f"ASCII: {ord(c):3d}  XOR con {85 + i:3d} ({hex(85 + i)}) = {operacion:4d}")
            print(f"Suma acumulada: {suma}\n")
    
    valida = suma == 1337
    return valida, suma

def generar_clave():
    caracteres = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+-=[]{}|;:,.<>?'
    target = 1337
    longitud = 9
    
    for combo in itertools.product(caracteres, repeat=longitud):
        clave = ''.join(combo)
        valida, suma = verificar_clave(clave)
        if valida:
            return clave, suma
    return None, None

def main():
    parser = argparse.ArgumentParser(description='Herramienta para el reto de seguridad', 
                                   formatter_class=argparse.RawTextHelpFormatter)
    parser.add_argument('-g', '--generar', action='store_true', 
                      help='Generar nueva clave válida (puede tomar varios minutos)')
    parser.add_argument('-v', '--verificar', metavar='CLAVE', type=str,
                      help='Verificar una clave específica\nEjemplo: -v "MiClave123"')
    
    args = parser.parse_args()
    
    if args.generar:
        print("\n🔓 Generando clave válida...")
        print("⚠️  Esto puede tomar entre 2-15 minutos dependiendo de tu hardware")
        clave, suma = generar_clave()
        
        if clave:
            print("\n🔥 Clave válida encontrada!")
            print(f"🔑 Clave: {clave}")
            print(f"🔢 Longitud: {len(clave)} caracteres")
            print(f"🧮 Suma total: {suma} (0x{suma:04x})")
            print("\nModo de uso:")
            print(f"  ./reto1")
            print(f"  Password: {clave}")
        else:
            print("\n❌ No se encontró ninguna clave válida con los caracteres permitidos")
    
    elif args.verificar:
        print(f"\n🔍 Verificando clave: '{args.verificar}'")
        valida, suma = verificar_clave(args.verificar, verbose=True)
        
        print("\n📊 Resultados:")
        print(f"Longitud: {len(args.verificar)} caracteres")
        print(f"Suma total obtenida: {suma} (0x{suma:04x})")
        print(f"Suma requerida: 1337 (0x0539)")
        print(f"Validez: {'✅ VÁLIDA' if valida else '❌ INVÁLIDA'}")
        
        if valida:
            print("\n🎉 ¡Clave correcta! Ejecuta con:")
            print(f"  echo -n '{args.verificar}' | ./reto1")
        else:
            diferencia = 1337 - suma
            print(f"\n⚠️  Diferencia: {diferencia} ({'Falta sumar' if diferencia > 0 else 'Sobrepasa por'} {abs(diferencia)})")
    
    else:
        parser.print_help()

if __name__ == '__main__':
    main()
