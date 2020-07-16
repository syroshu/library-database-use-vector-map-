#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <map>
#include <cctype>
#include <cstring>

using namespace std;

vector<int> rak;
vector<string> listjudul;
map<string, int> stok_buku;
map<string, int>pinjam_buku;

void togjudul(string& a){
	int length = a.length(); 
	for (int i = 0; i < length; i++) { 
		if(a[i]==95){
			a[i+1]=toupper(a[i+1]);
		}		 
	} 
	int c = a[0];
	a[0]=toupper(c);
}

int selectrak(string& a){ 
	int c = a[0];
	if(c>=65 && c<=70){
		return 1;
	}
	else if(c>=71 && c<=76){
		return 2;
	}
	else if(c>=77 && c<=82){
		return 3;
	}
	else if(c>=83 && c<=88){
		return 4;
	}
	else if((c==89 && c==90)||(c>=48 && c<=51)){
		return 5;
	}
	else if(c>=52 && c<=57){
		return 6;
	}
} 

int main(){
	string a;
	int indeks_buku=0;
	int indeks_judul=0;
	int menu = 1;
	
	for (int i=1; i<=6; i++){
        rak.push_back(i); 
	}
		
	while(menu!=0){
		cout << "\nMenu Database Perpustakaan\n" << endl;
		cout << "1. Input buku\n2. Cari buku\n3. Peminjaman buku\n4. Pengembalian buku\n5. Informasi rak\n0. Exit\n";
		cout << "\nMenu : "; cin >> menu;
		cout << endl;
			
		if(menu==1){
			
			cout<<"format penulisan judul yaitu menggunakan _ untuk spasi"<<endl;
			cout<<"contoh : Harry_potter\n"<<endl;
			cout << "Masukkan judul buku : "; cin >> a;
			togjudul(a);
			if(listjudul.empty()){
				listjudul.push_back(a);
				stok_buku.insert({a,1});
				indeks_judul+=1;
			}
			else{
				int cek=0;
				for(int i=0; i<listjudul.size(); i++){
					if(listjudul.at(i) == a){
						stok_buku[a]+=1;
						cek=1;
					}
				}
				if(cek==0){
					listjudul.push_back(a);
					stok_buku.insert({a,1});
					indeks_judul+=1;
				}
			}
			cout<<"\nBuku berhasil dimasukkan"<<endl;
			cout<<"Buku disimpan rak nomor :"<<selectrak(a)<<endl;
			cout<<"Stok buku "<<a<<" saat ini berjumlah : "<<stok_buku[a]<<endl;
		}
		else if(menu==2){
			cout<<"Masukan buku yang dicari : "; cin>>a;
			togjudul(a);
			string indeks=a;
			bool cek=0;
			for(int i=0; i<listjudul.size(); i++){
				if(listjudul.at(i) == a){
					cout<<"\nBuku ada dalam perpustakaan"<<endl;
					cout<<"Buku ada di rak nomor :"<<selectrak(a)<<endl;
					cout<<"Stok buku "<<indeks<<" ada : "<<stok_buku[indeks]<<endl;
					cek=1;
				}
			}
			if(cek==0){
				cout<<"Buku tidak ada dalam perpustakaan\n"<<endl;
			}
		}
		else if(menu==3){
			cout<<"Judul buku yang ingin dipinjam : "; cin>>a;
			togjudul(a);
			bool cek=0;	
			if(stok_buku[a]==0){
				cout<<"Buku ini tidak tersedia\n"<<endl;
			}
			for(int i=0; i<listjudul.size(); i++){
				if(listjudul.at(i) == a){
					if(stok_buku[a]==0){
						cout<<"\nSemua buku dengan judul ini sudah habis dipinjam"<<endl;
					}
					else{
						stok_buku[a]-=1;
						pinjam_buku.insert({a,0});
						pinjam_buku[a]+=1;
						cout<<"\nBuku berhasil dipinjam"<<endl;
						cout<<"Stok buku "<<a<<" saat ini berjumlah : "<<stok_buku[a]<<endl;
						cout<<"Buku "<<a<<" yang dipinjam berjumlah : "<<pinjam_buku[a]<<endl;
						cek=1;
					}
				}
			}
			if(cek==0){
				cout<<"Buku tidak tersedia\n"<<endl;
			}
		}
		else if(menu==4){
			cout<<"Masukkan judul buku yang dikembalikan : "; cin>>a;
			togjudul(a);	
			int cek=0;
			for(int i=0; i<listjudul.size(); i++){
				if(listjudul.at(i) == a){
					stok_buku[a]+=1;
					pinjam_buku[a]-=1;
					cout<<"\nStok buku "<<a<<" saat ini berjumlah : "<<stok_buku[a]<<endl;
					cout<<"Buku "<<a<<" yang dipinjam berjumlah : "<<pinjam_buku[a]<<endl;
					cout<<"Buku telah berhasil dikembalikan"<<endl;
					cek=1;
				}
			}
			
			if(cek==0){
				cout<<"\nBuku ini tidak terdata sebagai milik perpustakaan"<<endl;
			}
		}
		else if(menu==5){
			bool cek=0;
			int rak_cari;
			int nomor=1;
			cout<<"Masukkan rak yang ingin dicari : "; cin>>rak_cari;
			cout<<"\nNO JUDUL "<<endl;
			for(int i=0; i<listjudul.size(); i++){
				if(selectrak(listjudul.at(i))==rak_cari){
					cout<<nomor<<". "<<listjudul.at(i)<<"("<<stok_buku[listjudul.at(i)]<<")"<<endl;
					nomor+=1;
					cek=1;
				}
			}	
			if(cek==0){
				cout<<"\nRak masih kosong"<<endl;
			}
		}
	}	
}
